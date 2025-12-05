/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MiniIRCd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:58:49 by dgerhard          #+#    #+#             */
/*   Updated: 2025/11/30 08:49:36 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// MY COMMENT AGAIN

#include "MiniIRCd.hpp"
#include "IRCParser.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h> 
#include <poll.h>
#include <errno.h>
#include <string.h>
 #include <arpa/inet.h>
#include <stdio.h>

#include <iostream>
#include <sstream>
#include <algorithm>

#define MAXLINE 512
#define LISTEN_BACKLOG 16
#define MAX_EAGAIN_RETRIES 5

MiniIRCd::MiniIRCd(const std::string& port, const std::string& password)
    : port_(port), server_password_(password), listenfd_(-1) {}
MiniIRCd::~MiniIRCd() { if (listenfd_ != -1) close(listenfd_); }

int MiniIRCd::make_listen() {
	struct addrinfo hints, *res, *rp;
	int listenfd = -1, yes = 1;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	
	res = NULL;
	// std::cout << "res = " << res << "\n";
	
	int getaddrinfo_res = getaddrinfo(NULL, port_.c_str(), &hints, &res);
	if (getaddrinfo_res != 0)
	{
		std::cerr << "getaddrinfo failed\n";
		if (res == NULL)
			std::cerr << "res == NULL\n";

		return -1;
	}
	else
	{
		if (res == NULL)
			std::cerr << "res == NULL\n";
		else 
		{
			std::cout << "res = " ;
		    const struct sockaddr_in *addr4 =
    			reinterpret_cast<const struct sockaddr_in*>(res->ai_addr);
			char ipStr[INET_ADDRSTRLEN];   // 16 octets, assez grand pour IPv4
			inet_ntop(AF_INET, &(addr4->sin_addr), ipStr, sizeof(ipStr));
			std::cout << "Adresse IP retournée par getaddrinfo : " << ipStr << '\n';
		}
			
		std::cerr << "getaddrinfo SUCCESS, ans res = " << res << " \n";
	}


	int hah= 1;
	for (rp = res; rp; rp = rp->ai_next) {

		std::cout << "Try n°" << hah << ", res_addr = " << res->ai_addr->sa_data[0] << "\n";

		listenfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		// error:
		if (listenfd < 0) continue;
		setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
		
		int bind_res = bind(listenfd, rp->ai_addr, rp->ai_addrlen) ;
		if (bind_res == 0)
		{
			std::cout << "Found address n°" << hah << ", " ;
			const struct sockaddr_in *addr4 =
    			reinterpret_cast<const struct sockaddr_in*>(res->ai_addr);
			char ipStr[INET_ADDRSTRLEN];   // 16 octets, assez grand pour IPv4
			inet_ntop(AF_INET, &(addr4->sin_addr), ipStr, sizeof(ipStr));
			std::cout  << ipStr << '\n';
			// << rp->ai_addr->sa_data << std::endl;
			break;
		}
		else 
		{
			close(listenfd);
			listenfd = -1;
			std::cout << "Didn't find address n°" << hah << ", " << rp->ai_addr->sa_data << std::endl;
		}
		hah++;
	}
	freeaddrinfo(res);
	if (listenfd < 0) return -1;
	if (listen(listenfd, LISTEN_BACKLOG) < 0) { close(listenfd); return -1; }
	
	// We'll probably have avoid using "int flags"
	int flags = fcntl(listenfd, F_GETFL, 0);
	fcntl(listenfd, F_SETFL, flags | O_NONBLOCK);
	// fcntl(fd, F_SETFL, O_NONBLOCK); cf SUBJECT
	
	return listenfd;
}

int MiniIRCd::find_pollfd_index(int fd) {
	for (size_t i = 0; i < pfds_.size(); ++i) {
		if (pfds_[i].fd == fd) return (int)i;
	}
	return -1;
}

void MiniIRCd::flush_outgoing(int idx)
{
	if (idx < 0 || (size_t)idx >= pfds_.size()) return;
	int fd = pfds_[idx].fd;
	User &u = users_.at(fd);
	while (!u.outbuf.empty()) {
		ssize_t n = ::send(fd, u.outbuf.data(), u.outbuf.size(), MSG_NOSIGNAL);
		if (n > 0) {
			u.outbuf.erase(0, (size_t)n);
			continue;
		}
		if (n == -1) {
			if (errno == EINTR) continue;
			if (errno == EAGAIN || errno == EWOULDBLOCK) {
				// socket not writable now; keep data in outbuf and wait for next POLLOUT
				return;
			}
			// unrecoverable error -> close client
			std::cerr << "flush_outgoing: send error fd=" << fd << " errno=" << errno << "\n";
			// best-effort cleanup: simulate quit (use existing handler)
			handle_quit(fd, pfds_, idx);
			return;
		}
		// n == 0 means peer closed -> cleanup
		handle_quit(fd, pfds_, idx);
		return;
	}
	// if we drained the buffer, stop listening for POLLOUT
	pfds_[idx].events &= ~POLLOUT;
	pfds_[idx].events |= POLLIN;
}

void MiniIRCd::sendLine(int fd, const std::string& line) {
	std::string out = line + "\r\n";
	if (out.empty()) return;
	// try an immediate send first
	User &u = users_.at(fd);
	ssize_t n = ::send(fd, out.data(), out.size(), MSG_NOSIGNAL);
	if (n > 0) {
		if ((size_t)n == out.size()) {
			return; // fully sent
		}
		// partial send: buffer remainder
		u.outbuf.append(out.data() + n, out.size() - (size_t)n);
	} else if (n == -1) {
		if (errno == EINTR) {
			// try again once
			n = ::send(fd, out.data(), out.size(), MSG_NOSIGNAL);
			if (n > 0) {
				if ((size_t)n == out.size()) return;
				u.outbuf.append(out.data() + n, out.size() - (size_t)n);
			} else if (n == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
				u.outbuf.append(out);
			} else {
				std::cerr << "sendLine: unrecoverable send error fd=" << fd << " errno=" << errno << "\n";
				int idx = find_pollfd_index(fd);
				handle_quit(fd, pfds_, idx);
				return;
			}
		} else if (errno == EAGAIN || errno == EWOULDBLOCK) {
			// socket would block: queue entire message
			u.outbuf.append(out);
		} else {
			std::cerr << "sendLine: unrecoverable send error fd=" << fd << " errno=" << errno << "\n";
			int idx = find_pollfd_index(fd);
			handle_quit(fd, pfds_, idx);
			return;
		}
	} else {
		// n == 0: peer closed
		int idx = find_pollfd_index(fd);
		handle_quit(fd, pfds_, idx);
		return;
	}

	// ensure we will be notified when socket becomes writable
	int idx = find_pollfd_index(fd);
	if (idx >= 0) {
		pfds_[idx].events |= POLLOUT;
	}
}



static void debug_print_raw(const std::string &label, const std::string &s) {
	// print printable chars and hex for others (helps to see CR/LF/extra bytes)
	std::cerr << label << ": ";
	for (size_t i = 0; i < s.size(); ++i) {
		unsigned char c = static_cast<unsigned char>(s[i]);
		if (c >= 0x20 && c <= 0x7e) std::cerr << s[i];
		else {
			char buf[8];
			snprintf(buf, sizeof(buf), "\\x%02x", c);
			std::cerr << buf;
		}
	}
	std::cerr << std::endl;
}

static std::string nick_or_fd(const User& u) {
	if (!u.nick.empty()) return u.nick;
	std::ostringstream os; os << "fd" << u.usr_fd; return os.str();
}

void MiniIRCd::send_numeric(int fd, const std::string& target, int code, const std::string& msg) {
	std::ostringstream os;
	std::string tgt = target.empty() ? "*" : target;
	std::string text = msg;
	if (!text.empty() && text[0] == ':') text = text.substr(1);
	os << ":" << "miniircd" << " " << std::setw(3) << std::setfill('0') << (code)
		<< " " << tgt << " :" << text;
	sendLine(fd, os.str());
}

void MiniIRCd::handle_ping(const IRCMessage& msg, const int& fd)
{
	if (!msg.trailing.empty()) {
		std::ostringstream os; os << "PONG :" << msg.trailing;
		sendLine(fd, os.str());
	} else if (!msg.params.empty()) {
		std::ostringstream os; os << "PONG :" << msg.params[0];
		sendLine(fd, os.str());
	}
}

void MiniIRCd::handle_nick(const IRCMessage& msg, const int& fd)
{
	std::string newnick;
	if (!msg.params.empty()) newnick = msg.params[0];
	if (newnick.empty()) {
		sendLine(fd, "431 * :No nickname given");
	} else {
		if (newnick[0] == ':') newnick = newnick.substr(1);
		if (nick_map_.find(newnick) != nick_map_.end()) {
			sendLine(fd, (std::string("433 * ") + newnick + " :Nickname is already in use"));
		} else {
			User& u = users_.at(fd);
			if (!server_password_.empty() && !u.pass_ok) {
				sendLine(fd, "464 * :Password required");
				return ;
			}
			if (!u.nick.empty()) nick_map_.erase(u.nick);
			u.nick = newnick;
			nick_map_[newnick] = fd;
			if (!u.user.empty() && !u.registered) {
				u.registered = true;
				send_numeric(fd, u.nick, 001, ":Welcome to miniircd, made by Jeanne and Dean");
			}
		}
	}
}

void MiniIRCd::handle_user(const IRCMessage& msg, const int& fd)
{
	if (msg.params.size() < 3) {
		sendLine(fd, "461 USER :Not enough parameters");
		return;
	}
		
	User& u = users_.at(fd);
	if (!server_password_.empty() && !u.pass_ok) {
		sendLine(fd, "464 * :Password required");
		return ;
	}
	
	u.user = msg.params[0];
	if (!msg.trailing.empty()) u.real = msg.trailing;
	if (!u.nick.empty() && !u.registered) {
		u.registered = true;
		send_numeric(fd, u.nick, 001, ":Welcome to miniircd, made by Jeanne and Dean");
	}
}

void MiniIRCd::handle_join(const IRCMessage& msg, const int& fd)
{
	if (msg.params.empty())
		sendLine(fd, "461 JOIN :Not enough parameters");
	else
	{
		//max channel name length (including #) is 200 characters
		std::string chan = msg.params[0];
		if (chan.empty())
			return ; //return 461 response

		if (chan[0] != '#')
			chan = std::string("#") + chan;
		User usr = users_.at(fd);
		
		std::map<std::string, Channel>::iterator chan_it = channels_.find(chan);
		bool join_success = true;
		std::string detected_error = "";
		
		// This channel doesn't exist yet
		if (chan_it == channels_.end())
		{
			// Update 2 of the server's lists
			channels_[chan] = Channel(chan, usr);
			chnl_members_[chan].push_back(fd);
			// No errors expected
		}
		else
		{
			Channel existing_channel = chan_it->second;
			join_success = existing_channel.channel_join(usr, "", detected_error);
			if (!join_success)
			{
				sendLine(fd, detected_error);
				return;
			}
		}

		std::ostringstream joinmsg;
		joinmsg << ":" << nick_or_fd(usr) << " JOIN :" << chan;
		for (size_t k = 0; k < chnl_members_[chan].size(); ++k)
			sendLine(chnl_members_[chan][k], joinmsg.str());
		
		std::ostringstream names;
		names << ":miniircd 353 " << (usr.nick.empty() ? "*" : usr.nick) << " = " << chan << " :";
		for (size_t k = 0; k < chnl_members_[chan].size(); ++k)
		{
			User& a_user = users_.at(chnl_members_[chan][k]);
			names << (a_user.nick.empty() ? nick_or_fd(a_user) : a_user.nick) << (k + 1 < chnl_members_[chan].size() ? " " : "");
		}
		sendLine(fd, names.str());
		std::ostringstream endnames;
		endnames << ":miniircd 366 " << (usr.nick.empty() ? "*" : usr.nick) << " " << chan << " :End of /NAMES list.";
		sendLine(fd, endnames.str());
	}
}

void MiniIRCd::handle_privmsg(const IRCMessage& msg, const int& fd)
{
	if (msg.params.empty()) { sendLine(fd, "411 :No recipient given"); return ; }
	std::string target = msg.params[0];
	std::string text = msg.trailing;
	User& sender = users_.at(fd);
	if (target.size() > 0 && target[0] == '#') {
		std::vector<int>& v = chnl_members_[target];
		for (size_t k=0;k<v.size();++k) {
			if (v[k] == fd) continue;
			std::ostringstream pm;
			pm << ":" << nick_or_fd(sender) << " PRIVMSG " << target << " :" << text;
			sendLine(v[k], pm.str());
		}
	} else {
		std::map<std::string,int>::iterator it = nick_map_.find(target);
		if (it == nick_map_.end()) {
			sendLine(fd, (std::string("401 ") + target + " :No such nick/channel"));
		} else {
			int od = it->second;
			std::ostringstream pm;
			pm << ":" << nick_or_fd(sender) << " PRIVMSG " << target << " :" << text;
			sendLine(od, pm.str());
		}
	}
}

void MiniIRCd::handle_quit(const int& fd, std::vector<struct pollfd>& pfds, int i)
{
	User u = users_.at(fd);
	std::ostringstream q;
	q << ":" << nick_or_fd(u) << " QUIT :Client Quit";
	for (std::map<std::string, std::vector<int> >::iterator it=chnl_members_.begin(); it!=chnl_members_.end(); ++it)
	{
		std::vector<int>& v = it->second;
		for (size_t k = 0; k < v.size(); ++k)
			if (v[k] != fd)
				sendLine(v[k], q.str());
	}
	sendLine(fd, "ERROR :Closing Link");
	close(fd);
	if (!u.nick.empty()) nick_map_.erase(u.nick);
	users_.erase(fd);
	pfds.erase(pfds.begin()+i);
	std::cout << "fd " << fd << " quit\n";
}

//does not print nick upon exit
void MiniIRCd::handle_cap(const IRCMessage& msg, const int& fd)
{
	std::string sub = msg.params.size() ? msg.params[0] : "";
	std::string args = !msg.trailing.empty() ? msg.trailing : (msg.params.size() > 1 ? msg.params[1] : "");

	const std::string supported = "End of CAP LS negotiation";

	if (sub == "LS") {
		sendLine(fd, std::string("CAP * LS :") + supported);
	} else if (sub == "REQ") {
		std::istringstream iss(args);
		std::string cap;
		std::vector<std::string> ack, nak;
		while (iss >> cap) {
			if (!cap.empty() && supported.find(cap) != std::string::npos) ack.push_back(cap);
			else nak.push_back(cap);
		}
		if (!ack.empty()) {
			std::ostringstream os; os << "CAP * ACK :";
			for (size_t i=0;i<ack.size();++i) { if (i) os << ' '; os << ack[i]; }
			sendLine(fd, os.str());
		}
		if (!nak.empty()) {
			std::ostringstream os; os << "CAP * NAK :";
			for (size_t i=0;i<nak.size();++i) { if (i) os << ' '; os << nak[i]; }
			sendLine(fd, os.str());
		}
	} else if (sub == "END") {
	} else {
		sendLine(fd, std::string(":miniircd NOTICE * :Unknown CAP subcommand"));
	}
}

void MiniIRCd::handle_pass(const IRCMessage& msg, const int& fd, std::vector<struct pollfd>& pfds, int i)
{
	if (msg.params.empty()) {
		sendLine(fd, "461 PASS :Not enough parameters");
		return;
	}
	std::string pw = msg.params[0];
	if (!pw.empty() && pw[0] == ':') pw = pw.substr(1);

	if (server_password_.empty()) {
		users_[fd].pass_ok = true;
		return;
	}

	if (pw == server_password_) {
		users_[fd].pass_ok = true;
	} else {
		sendLine(fd, "464 * :Password incorrect");
		handle_quit(fd, pfds, i);
	}
}


int MiniIRCd::run()
{
	listenfd_ = make_listen();
	if (listenfd_ < 0)
	{
		std::cerr << "listen failed\n";
		return 1;
	}

	std::cout << "listening on port " << port_ << "\n";

	pfds_.push_back(pollfd());
	// the server's main socket is on pfds_[0]:
	pfds_[0].fd = listenfd_; pfds_[0].events = POLLIN;

	while (1)
	{
		//if incoming connection, poll[0].revents will be set to POLLIN
		int rc = poll(&pfds_[0], pfds_.size(), -1);
		if (rc < 0)
		{
			if (errno == EINTR) continue;
			break;
		}
		// incoming new connection :
		if (pfds_[0].revents & POLLIN)
		{ 
			int newfd = accept(listenfd_, NULL, NULL);
			if (newfd >= 0)
			{
				fcntl(newfd, F_SETFL, O_NONBLOCK);
				User usr(newfd);
				users_[newfd] = usr;
				struct pollfd p; p.fd = newfd; p.events = POLLIN; p.revents = 0;
				pfds_.push_back(p);
				std::cout << "accept fd = " << newfd << "\n";
			}
		}
		//iterate through each client and check what their status is :
		for (int i = (int)pfds_.size() - 1; i >= 1; --i)
		{ 
			int client_fd = pfds_[i].fd;
			short re = pfds_[i].revents;
			if (re == 0)
				continue;
			if (re & (POLLERR | POLLHUP | POLLNVAL))
				re = POLLIN;
			if (re & POLLIN)
			{
				char buf[1024];
				ssize_t n = recv(client_fd, buf, sizeof(buf), 0);
				if (n <= 0)
				{
					// We are sure that users_.at(client_fd) has returned
					// a reference to a User instance :
					User usr = users_.at(client_fd);
					std::string quitmsg = (usr.registered ? usr.nick : std::string("guest")) + " has quit";
					
					// erase the fd of the user who quitted the server
					// from each channel :
					std::map<std::string, std::vector<int> >::iterator it;
					for (it = chnl_members_.begin(); it != chnl_members_.end(); ++it)
					{
						std::vector<int> channel_fds = it->second;
						for (size_t k = 0; k < channel_fds.size(); ++k)
						{
							if (channel_fds[k] == client_fd)
								continue;
							// tell other users of this channel, that smbdy has quit :
							std::ostringstream os;
							// os << ":" << nick_or_fd(c) << " QUIT :" << quitmsg;
							os << ":" << usr.usr_fd << " QUIT :" << quitmsg;
							sendLine(channel_fds[k], os.str());
						}

						std::vector<int> channel_new_fds;
						for (size_t k = 0;k < channel_fds.size(); ++k)
						{
							if (channel_fds[k] != client_fd)
								channel_new_fds.push_back(channel_fds[k]);
						}
						channel_fds.swap(channel_new_fds);
					}
					// And erase quitted user from server's list
					if (!usr.nick.empty())
						nick_map_.erase(usr.nick);
					close(client_fd);
					users_.erase(client_fd);
					pfds_.erase(pfds_.begin() + i);
					std::cout << "fd " << client_fd << " disconnected\n";
					continue;
				} 
				else
				{
					// We are sure that users_.at(client_fd) will return
					// a reference to a User instance :
					// (otherwise .at() throws an exception)
					User actual_user = users_.at(client_fd);
					actual_user.inbuf.append(buf, buf + n);
					size_t pos;
					while ((pos = actual_user.inbuf.find("\r\n")) != std::string::npos ||
						(pos = actual_user.inbuf.find("\n")) != std::string::npos)
					{
						std::string line = actual_user.inbuf.substr(0, pos);
						size_t erase_len = 1; 
						if (actual_user.inbuf.size() > pos && actual_user.inbuf[pos] == '\r') {
							if (actual_user.inbuf.size() > pos+1 && actual_user.inbuf[pos+1] == '\n') erase_len = 2;
						} else {
							erase_len = 1;
						}
						actual_user.inbuf.erase(0, pos + erase_len);

						if (line.size() > MAXLINE) line = line.substr(0, MAXLINE);
						debug_print_raw("RECV raw", line);

						IRCMessage msg = parseLine(line);
						std::string cmd = msg.command;
						for (size_t u=0; u<cmd.size(); ++u) cmd[u] = toupper(cmd[u]);

						//put all this into "handle_command"
						if (cmd == "PING") {
							handle_ping(msg, client_fd);
						} else if (cmd == "PASS") {
							handle_pass(msg, client_fd, pfds_, i);
						} else if (cmd == "NICK") {
							handle_nick(msg, client_fd);
						} else if (cmd == "USER") {
							handle_user(msg, client_fd);
						} else if (cmd == "JOIN") {
							// /!\ Join should handle several channels with eventual pswds
							// example : JOIN #channel,#channel2 pswd,pswd2(or nothing as pswd)
							// https://modern.ircdocs.horse/#join-message 
							// How to handle it inside IRCMessage?
							handle_join(msg, client_fd);
						} else if (cmd == "PRIVMSG") {
							handle_privmsg(msg, client_fd);
						} else if (cmd == "CAP") {
							handle_cap(msg, client_fd);
						} else if (cmd == "QUIT") {
							handle_quit(client_fd, pfds_, i);
							break;
						} else {
							sendLine(client_fd, std::string(":miniircd NOTICE * :Unknown command ") + cmd);
						}
					} // end processing lines
				}
			} // end POLLIN
			if (re & POLLOUT)
				flush_outgoing(i);
		} // end clients loop
	} // main loop

	close(listenfd_);
	return 0;
}