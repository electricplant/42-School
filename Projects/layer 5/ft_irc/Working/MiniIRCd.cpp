/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MiniIRCd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:58:49 by dgerhard          #+#    #+#             */
/*   Updated: 2025/11/24 08:59:05 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

#include <stdio.h>

#include <iostream>
#include <sstream>
#include <algorithm>

#define MAXLINE 512
#define LISTEN_BACKLOG 16

MiniIRCd::MiniIRCd(const std::string& port) : port_(port), listenfd_(-1) {}
MiniIRCd::~MiniIRCd() { if (listenfd_ != -1) close(listenfd_); }

int MiniIRCd::make_listen() {
	struct addrinfo hints, *res, *rp;
	int listenfd = -1, yes = 1;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	if (getaddrinfo(NULL, port_.c_str(), &hints, &res) != 0) return -1;
	for (rp = res; rp; rp = rp->ai_next) {
		listenfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (listenfd < 0) continue;
		setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
		if (bind(listenfd, rp->ai_addr, rp->ai_addrlen) == 0) break;
		close(listenfd);
		listenfd = -1;
	}
	freeaddrinfo(res);
	if (listenfd < 0) return -1;
	if (listen(listenfd, LISTEN_BACKLOG) < 0) { close(listenfd); return -1; }
	int flags = fcntl(listenfd, F_GETFL, 0);
	fcntl(listenfd, F_SETFL, flags | O_NONBLOCK);
	return listenfd;
}

static void sendLine(int fd, const std::string& line) {
	std::string out = line + "\r\n";
	size_t sent = 0;
	while (sent < out.size()) {
		ssize_t n = send(fd, out.data() + sent, out.size() - sent, 0);
		if (n <= 0) break;
		sent += n;
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

static std::string nick_or_fd(const Client& c) {
	if (!c.nick.empty()) return c.nick;
	std::ostringstream os; os << "fd" << c.fd; return os.str();
}

static void send_numeric(int fd, const std::string& target, int code, const std::string& msg) {
	std::ostringstream os;
	std::string tgt = target.empty() ? "*" : target;
	std::string text = msg;
	if (!text.empty() && text[0] == ':') text = text.substr(1);
	os << ":" << "miniircd" << " " << std::setw(3) << std::setfill('0') << (code)
		<< " " << tgt << " :" << text;
	sendLine(fd, os.str());
}


//CABLE MANAGEMENT

void MiniIRCd::handle_ping(const IRCMessage& msg, const int& fd, const std::string& line)
{
		debug_print_raw("RECV PING raw", line);

	if (!msg.trailing.empty()) {
		sendLine(fd, (std::string("weird3")));
		std::ostringstream os; os << "PONG :" << msg.trailing;
		sendLine(fd, os.str());
	} else if (!msg.params.empty()) {
		sendLine(fd, (std::string("weird2")));
		std::ostringstream os; os << "PONG :" << msg.params[0];
		sendLine(fd, os.str());
	} else {
		sendLine(fd, (std::string("weird")));
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
			Client& c = clients_[fd];
			if (!c.nick.empty()) nick_map_.erase(c.nick);
			c.nick = newnick;
			nick_map_[newnick] = fd;
			if (!c.user.empty() && !c.registered) {
				c.registered = true;
				send_numeric(fd, c.nick, 001, ":Welcome to miniircd");
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
		
	Client& c = clients_[fd];
	c.user = msg.params[0];
	if (!msg.trailing.empty()) c.real = msg.trailing;
	if (!c.nick.empty() && !c.registered) {
		c.registered = true;
		send_numeric(fd, c.nick, 001, ":Welcome to miniircd");
	}
}

void MiniIRCd::handle_join(const IRCMessage& msg, const int& fd)
{
		if (msg.params.empty()) {
		sendLine(fd, "461 JOIN :Not enough parameters");
	} else {
		std::string chan = msg.params[0];
		if (chan.empty()) return ;
		if (chan[0] != '#') chan = std::string("#") + chan;
		Client& c = clients_[fd];
		std::vector<int>& v = channels_[chan];
		bool already = false;
		for (size_t k=0;k<v.size();++k) if (v[k]==fd) { already = true; break; }
		if (!already) v.push_back(fd);
		
		std::ostringstream joinmsg;
		joinmsg << ":" << nick_or_fd(c) << " JOIN :" << chan;
		for (size_t k=0;k<v.size();++k) sendLine(v[k], joinmsg.str());
		std::ostringstream names;
		names << ":miniircd 353 " << (c.nick.empty() ? "*" : c.nick) << " = " << chan << " :";
		for (size_t k=0;k<v.size();++k) {
			Client& oc = clients_[v[k]];
			names << (oc.nick.empty() ? nick_or_fd(oc) : oc.nick) << (k+1<v.size() ? " " : "");
		}
		sendLine(fd, names.str());
		std::ostringstream endnames;
		endnames << ":miniircd 366 " << (c.nick.empty() ? "*" : c.nick) << " " << chan << " :End of /NAMES list.";
		sendLine(fd, endnames.str());
	}
}

void MiniIRCd::handle_privmsg(const IRCMessage& msg, const int& fd)
{
	if (msg.params.empty()) { sendLine(fd, "411 :No recipient given"); return ; }
	std::string target = msg.params[0];
	std::string text = msg.trailing;
	Client& sender = clients_[fd];
	if (target.size() > 0 && target[0] == '#') {
		std::vector<int>& v = channels_[target];
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
	Client c = clients_[fd];
	std::ostringstream q;
	q << ":" << nick_or_fd(c) << " QUIT :Client Quit";
	for (std::map<std::string, std::vector<int> >::iterator it=channels_.begin(); it!=channels_.end(); ++it) {
		std::vector<int>& v = it->second;
		for (size_t k=0;k<v.size();++k) if (v[k] != fd) sendLine(v[k], q.str());
	}
	sendLine(fd, "ERROR :Closing Link");
	close(fd);
	if (!c.nick.empty()) nick_map_.erase(c.nick);
	clients_.erase(fd);
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
//END CABLE MANAGEMENT

int MiniIRCd::run() {
	listenfd_ = make_listen();
	if (listenfd_ < 0) { std::cerr << "listen failed\n"; return 1; }
	std::cout << "listening on port " << port_ << "\n";

	std::vector<struct pollfd> pfds;
	pfds.push_back(pollfd());
	pfds[0].fd = listenfd_; pfds[0].events = POLLIN;

	while (1) {
		int rc = poll(&pfds[0], pfds.size(), -1); //if incoming connection, poll[0].revents will be set to POLLIN
		if (rc < 0) {
			if (errno == EINTR) continue;
			break;
		}
		if (pfds[0].revents & POLLIN) { // = incoming connection
			int newfd = accept(listenfd_, NULL, NULL);
			if (newfd >= 0) {
				int flags = fcntl(newfd, F_GETFL, 0);
				fcntl(newfd, F_SETFL, flags | O_NONBLOCK);
				Client c; c.fd = newfd; c.registered = false;
				clients_[newfd] = c;
				struct pollfd p; p.fd = newfd; p.events = POLLIN; p.revents = 0;
				pfds.push_back(p);
				std::cout << "accept fd=" << newfd << "\n";
			}
		}
		for (int i = (int)pfds.size()-1; i >= 1; --i) { //iterate through each user and check what their status is
			int fd = pfds[i].fd;
			short re = pfds[i].revents;
			if (re == 0) continue;
			if (re & (POLLERR|POLLHUP|POLLNVAL)) re = POLLIN;
			if (re & POLLIN) {
				char buf[1024];
				ssize_t n = recv(fd, buf, sizeof(buf), 0);
				if (n <= 0) {
					Client c = clients_[fd];
					std::string quitmsg = (c.registered ? c.nick : std::string("guest")) + " has quit";
					for (std::map<std::string, std::vector<int> >::iterator it=channels_.begin(); it!=channels_.end(); ++it) {
						std::vector<int>& v = it->second;
						for (size_t k=0;k<v.size();++k) {
							if (v[k] == fd) continue;
							std::ostringstream os;
							os << ":" << nick_or_fd(c) << " QUIT :" << quitmsg;
							sendLine(v[k], os.str());
						}
						std::vector<int> nv;
						for (size_t k=0;k<v.size();++k) if (v[k] != fd) nv.push_back(v[k]);
						v.swap(nv);
					}
					if (!c.nick.empty()) nick_map_.erase(c.nick);
					close(fd);
					clients_.erase(fd);
					pfds.erase(pfds.begin()+i);
					std::cout << "fd " << fd << " disconnected\n";
					continue;
				} else {
					clients_[fd].inbuf.append(buf, buf + n);
					size_t pos;
					while ((pos = clients_[fd].inbuf.find("\r\n")) != std::string::npos ||
						(pos = clients_[fd].inbuf.find("\n")) != std::string::npos) {
						std::string line = clients_[fd].inbuf.substr(0, pos);
						size_t erase_len = 1;
						if (clients_[fd].inbuf.size() > pos && clients_[fd].inbuf[pos] == '\r') {
							if (clients_[fd].inbuf.size() > pos+1 && clients_[fd].inbuf[pos+1] == '\n') erase_len = 2;
						} else {
							erase_len = 1;
						}
						clients_[fd].inbuf.erase(0, pos + erase_len);

						if (line.size() > MAXLINE) line = line.substr(0, MAXLINE);
						debug_print_raw("RECV raw", line);

						IRCMessage msg = parseLine(line);
						std::string cmd = msg.command;
						for (size_t u=0; u<cmd.size(); ++u) cmd[u] = toupper(cmd[u]);

						
						if (cmd == "PING") {
							handle_ping(msg, fd, line);
						} else if (cmd == "NICK") {
							handle_nick(msg, fd);
						} else if (cmd == "USER") {
							handle_user(msg, fd);
						} else if (cmd == "JOIN") {
							handle_join(msg, fd);
						} else if (cmd == "PRIVMSG") {
							handle_privmsg(msg, fd);
						} else if (cmd == "CAP") {
							handle_cap(msg, fd);
						} else if (cmd == "QUIT") {
							handle_quit(fd, pfds, i);
							break;
						} else {
							sendLine(fd, std::string(":miniircd NOTICE * :Unknown command ") + cmd);
						}
					} // end processing lines
				}
			} // end POLLIN
		} // end clients loop
	} // main loop

	close(listenfd_);
	return 0;
}