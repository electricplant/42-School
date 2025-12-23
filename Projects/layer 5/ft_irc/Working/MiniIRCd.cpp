/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MiniIRCd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:58:49 by dgerhard          #+#    #+#             */
/*   Updated: 2025/12/11 12:47:07 by dgerhard         ###   ########.fr       */
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

volatile sig_atomic_t MiniIRCd::shutdown = 0;

static void signal_handler(int signum)
{
	(void)signum;
	MiniIRCd::shutdown = 1;
}

MiniIRCd::MiniIRCd(const std::string& port, const std::string& password)
    : oper_password_("operpass"), port_(port), server_password_(password), listenfd_(-1) {}
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


	int hah = 1;
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
	
	// We'll probably have to avoid using "int flags"
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
			handle_quit(fd, idx);
			return;
		}
		// n == 0 means peer closed -> cleanup
		handle_quit(fd, idx);
		return;
	}
	// if we drained the buffer, stop listening for POLLOUT
	pfds_[idx].events &= ~POLLOUT;
	pfds_[idx].events |= POLLIN;
}

void MiniIRCd::sendLine(int fd, const std::string& line)
{
	std::string out = line + "\r\n";
	if (out.empty()) return;
	
	User u = users_.at(fd);
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
				handle_quit(fd, idx);
				return;
			}
		} else if (errno == EAGAIN || errno == EWOULDBLOCK) {
			// socket would block: queue entire message
			u.outbuf.append(out);
		} else {
			std::cerr << "sendLine: unrecoverable send error fd=" << fd << " errno=" << errno << "\n";
			int idx = find_pollfd_index(fd);
			handle_quit(fd, idx);
			return;
		}
	} else {
		// n == 0: peer closed
		int idx = find_pollfd_index(fd);
		handle_quit(fd, idx);
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
	std::ostringstream os; os << "fd " << u.usr_fd; return os.str();
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
	if (!msg.params.empty())
		newnick = msg.params[0];
	if (newnick.empty())
	{
		sendLine(fd, "431 * :No nickname given");
	}
	else
	{
		if (newnick[0] == ':')
			newnick = newnick.substr(1);

		if (nick_map_.find(newnick) != nick_map_.end())
		{
			sendLine(fd, (std::string("433 * ") + newnick + " :Nickname is already in use"));
		}
		else
		{
			User& u = users_.at(fd);
			if (!server_password_.empty() && !u.pass_ok)
			{
				sendLine(fd, "464 * :Password required");
				return ;
			}
			std::string orignick = u.nick;
			if (!u.nick.empty())
				nick_map_.erase(orignick);

			u.nick = newnick;
			nick_map_[newnick] = fd;
			// if (!u.user.empty() && !u.registered)
			// {
				u.registered = true;
			// 	send_numeric(fd, u.nick, 001, ":Welcome to miniircd, made by Jeanne and Dean");
			// }
			// else
			// {
				// Tell the other users that smbdy changed his nick
				this->usr_it_ = users_.begin();
				while (this->usr_it_ != users_.end())
				{
					std::ostringstream nick_change;
					nick_change << ":" << orignick << "!~" << u.user << "@localhost NICK :" << newnick;
					sendLine(this->usr_it_->first, nick_change.str());
					this->usr_it_++;
				}
				// Confirm to the user himself
				if (u.nick.empty())
					sendLine(fd, nick_or_fd(u) + " NICK :" + newnick);
				else
					sendLine(fd, orignick + " NICK :" + newnick);

				send_numeric(fd, u.nick, 001, ":Welcome to miniircd, made by Jeanne and Dean");
			// }
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
	if (!msg.trailing.empty())
		u.real = msg.trailing;
	if (!u.nick.empty() && !u.registered)
	{
		u.registered = true;
		send_numeric(fd, u.nick, 001, ":Welcome to miniircd, made by Jeanne and Dean");
	}
}

void MiniIRCd::handle_join(const IRCMessage& msg, const int& fd)
{
	if (msg.params.empty())
		sendLine(fd, ":miniircd 461 JOIN :Not enough parameters");
	else
	{
		User usr = users_.at(fd);
		bool new_chanop = false;
		//max channel name length (including #) is 200 characters
		std::string chan = msg.params[0];
		if (chan.empty())
		{
			// ERR_NEEDMOREPARAMS (461)
			sendLine(fd, ":miniircd 461 " + nick_or_fd(usr) + " JOIN :Not enough parameters");
			return ;
		}

		if (chan[0] != '#')
			chan = std::string("#") + chan;
		
		this->chnls_it_ = channels_.find(chan);
		bool join_success = true;
		std::string detected_error = "";
		
		// This channel doesn't exist yet
		if (this->chnls_it_ == channels_.end())
		{
			std::cout << usr.nick << " joined " << chan << "\n";
			// Update 2 of the server's lists
			channels_[chan] = Channel(chan, usr.nick);
			chnl_members_[chan].push_back(fd);
			new_chanop = true;
			// No errors expected
		}
		else
		{
			Channel& existing_channel = this->chnls_it_->second;
			join_success = existing_channel.channel_join(usr.nick, "", detected_error);
			if (!join_success)
			{
				sendLine(fd, detected_error);
				return;
			}
			chnl_members_[chan].push_back(fd);
			std::cout << usr.nick << " joined " << chan << "\n";

		}

		// Warn all channel members :
		std::ostringstream joinmsg;
		// joinmsg << ":" << usr.nick << " JOIN :" << chan;
		joinmsg << ":" << usr.get_host_mask() << " JOIN :" << chan;
		for (size_t k = 0; k < chnl_members_[chan].size(); ++k)
			sendLine(chnl_members_[chan][k], joinmsg.str());
		
		// If it is a chanop
		if (new_chanop)
			sendLine(fd, ":miniircd MODE " + chan + " +o " + usr.nick);

		// Send topic to the new channel member - RPL_TOPIC (332)
		Channel& chnl = channels_.at(chan);
		if (!chnl.get_chnl_topic().empty())
			sendLine(fd, ":miniircd 332 " + usr.nick + " " + chan + " :" + chnl.get_chnl_topic());

		// Send list of chanel members to the new member
		std::ostringstream names;
		names << ":miniircd 353 " << (usr.nick.empty() ? "*" : usr.nick) << " = " << chan << " :";
		for (size_t k = 0; k < chnl_members_[chan].size(); ++k)
		{
			std::string prefix = "";
			User& a_user = users_.at(chnl_members_[chan][k]);
			bool is_chanop = chnl.is_chnl_op(a_user.nick);
			if (is_chanop)
				prefix = "@";
			names << (a_user.nick.empty() ? nick_or_fd(a_user) : prefix + a_user.nick) << (k + 1 < chnl_members_[chan].size() ? " " : "");
		}
		sendLine(fd, names.str());
		
		std::ostringstream endnames;
		endnames << ":miniircd 366 " << (usr.nick.empty() ? "*" : usr.nick) << " " << chan << " :End of /NAMES list.";
		sendLine(fd, endnames.str());



	}
}

// If the user types "/part " without a word starting whith "#"
// IRSSI considers that the user wants to quit the actual channel
// So "/part channel reason" -> "channel reason" will be considered
// as trailing, not /part's argument
void MiniIRCd::handle_part(const IRCMessage& msg, const int& fd)
{
	if (msg.params.empty()) {
		sendLine(fd, ":miniircd 461 PART :Not enough parameters");
		return;
	}

	std::string chan = msg.params[0];
	if (chan.empty())
		return;

	if (chan[0] != '#')
		chan = std::string("#") + chan;
	
	User& u = users_.at(fd);

	this->chnl_mem_it_ = chnl_members_.find(chan);
	if (this->chnl_mem_it_ == chnl_members_.end()) {
		sendLine(fd, ":miniircd 403 " + u.nick + " " + chan + " :No such channel");
		return;
	}
	// Such channel exists
	Channel& this_channel = this->channels_.at(chan);

	std::vector<int>& members = this->chnl_mem_it_->second;

	bool user_in_channel = false;
	for (size_t k = 0; k < members.size(); ++k) {
		if (members[k] == fd) {
			user_in_channel = true;
			break;
		}
	}

	if (!user_in_channel) {
		sendLine(fd, ":miniircd 442 " + u.nick + " " + chan + " :You're not even in there");
		return;
	}

	std::ostringstream part_msg;
	// part_msg << ":" << u.nick << "!~" << u.user << "@localhost PART " << chan;
	part_msg << ":" << u.get_host_mask() << " PART " << chan;
	if (!msg.trailing.empty()) {
		part_msg << " :" << msg.trailing;
	}

	for (size_t k = 0; k < members.size(); ++k) {
		if (users_.find(members[k]) != users_.end()) {
			sendLine(members[k], part_msg.str());
		}
	}

	// Update channel listw in MiniIRCd
	std::vector<int> new_members;
	for (size_t k = 0; k < members.size(); ++k) {
		if (members[k] != fd) {
			new_members.push_back(members[k]);
		}
	}
	members.swap(new_members);

	this_channel.channel_part(u.nick);
	if (members.empty()) {
		chnl_members_.erase(this->chnl_mem_it_);
		channels_.erase(chan);
	}

	std::cout << u.nick << " parted " << chan << "\n";	
}


void MiniIRCd::handle_privmsg(const IRCMessage& msg, const int& fd)
{
	if (msg.params.empty())
	{
		sendLine(fd, "411 :No recipient given");
		return ;
	}
	std::string target = msg.params[0];
	std::string text = msg.trailing;

	// std::map<int, User>::iterator usr_finder;
	this->usr_it_ = users_.find(fd);
	if (this->usr_it_ == users_.end()) 
		return ; // fd corresponds to no user

	User& sender = this->usr_it_->second;
	// send msg to a channel
	if (target.size() > 0 && target[0] == '#')
	{
		this->chnl_mem_it_ = this->chnl_members_.find(target);
		if (this->chnl_mem_it_ == this->chnl_members_.end())
		{
			// Attempt to send messages to non existing channel
			return;
		}

		std::vector<int>& v = this->chnl_mem_it_->second;
		for (size_t k = 0; k < v.size(); ++k)
		{
			if (v[k] == fd)
				continue;
			std::ostringstream pm;
			pm << ":" << nick_or_fd(sender) << " PRIVMSG " << target << " :" << text;
			sendLine(v[k], pm.str());
		}
	}
	else
	{
		// send msg to another user
		// std::map<std::string, int>::iterator it = nick_map_.find(target);
		this->nicks_it_ = nick_map_.find(target);
		if (this->nicks_it_ == nick_map_.end())
		{
			sendLine(fd, (std::string("401 ") + target + " :No such nick/channel"));
		}
		else
		{
			int od = this->nicks_it_->second;
			std::ostringstream pm;
			pm << ":" << nick_or_fd(sender) << " PRIVMSG " << target << " :" << text;
			sendLine(od, pm.str());
		}
	}
}

// better to just use const int fd, instead of its reference -> valgrind problems
void MiniIRCd::handle_quit(const int fd, int i)
{
	User u = users_.at(fd);
	std::ostringstream q;
	// q << ":" << nick_or_fd(u) << " QUIT :Client Quit";
	q << ":" << u.get_host_mask() << " QUIT :Client Quit";
	for (chnl_mem_it_ =chnl_members_.begin(); chnl_mem_it_!=chnl_members_.end(); ++chnl_mem_it_)
	{
		std::cout << "Eject user from channel " << chnl_mem_it_->first << std::endl;
		std::vector<int>& v = chnl_mem_it_->second;
		for (size_t k = 0; k < v.size(); ++k)
			if (v[k] != fd)
				sendLine(v[k], q.str()); // alert all group members
			else
				v.erase(v.begin() + k); // erase quitted user's fd
	}
	sendLine(fd, "ERROR :Closing Link");
	close(fd);
	nicks_it_ = nick_map_.find(u.nick);
	if (nicks_it_ != nick_map_.end())
		nick_map_.erase(u.nick);


	// std::map<int, User>::iterator u_it;
	// u_it = users_.find(fd);
	// if (u_it != users_.end())
	users_.erase(fd);
	// u_it = opers_.find(fd);
	// if (u_it != opers_.end())
	opers_.erase(fd);
	pfds_.erase(pfds_.begin() + i);
	std::cout << "fd " << fd << " quit\n";


	// std::cout << "AFTER QUIT : \n";
	// std::map<int, User>::iterator u_it = this->users_.begin();
	// std::cout << "list of users_ (" << this->users_.size() << ") :\n";
	// while (u_it != this->users_.end())
	// {
	// 	std::cout << u_it->second.nick << std::endl;
	// 	u_it++;
	// }
	// u_it = this->opers_.begin();
	// std::cout << "list of opers_ (" << this->opers_.size() << ") :\n";
	// while (u_it != this->opers_.end())
	// {
	// 	std::cout << u_it->second.nick << std::endl;
	// 	u_it++;
	// }
	// std::cout << "pfds size : " << pfds_.size() << "\n";
}

void MiniIRCd::handle_kill(const int killer_fd, const IRCMessage& msg)
{
	// Not oper
	
	this->usr_it_ = opers_.find(killer_fd);
	if (this->usr_it_ == opers_.end())
	{
		std::cout << "kill error 1\n";
		sendLine(killer_fd, "481 " + nick_or_fd(killer_fd) + " :Permission Denied- You're not an IRC operator");
		return ;
	}
	// Parameters
	if (msg.params.size() < 1 || msg.trailing.empty())
	{
		std::cout << "kill error 2: msg.params[0]: " << msg.params[0] << "\n";
		std::cout << "msg.params.size() : " << msg.params.size()  << "\n";

		sendLine(killer_fd, "461 " + this->usr_it_->second.nick + " KILL :Not enough parameters");
		return ;
	}
	// If it wants to kill a non existing user
	// std::map<std::string, int>::iterator nick_it;
	this->nicks_it_ = this->nick_map_.find(msg.params[0]);
	if (this->nicks_it_ == nick_map_.end())
	{
		std::cout << "kill error 3\n";
	
		// ERR_NOSUCHNICK (401)
		sendLine(killer_fd, "401 " + this->usr_it_->second.nick + msg.params[0] + " :No such nickname");
		return ;
	}
	
	// or kill himself or another operator
	this->usr_it_ = opers_.find(this->nicks_it_->second);
	if (this->usr_it_ != opers_.end() || this->nicks_it_->second == killer_fd)
	{
		std::cout << "kill error 4\n";

		sendLine(killer_fd, "483 KILL :You cant kill yourself or another operator!");
		return ;
	}

	// All OK, can kill
	sendLine(this->nicks_it_->second, "ERROR :You are kicked out of the server : " + msg.trailing);
	int victim_fd = -1;
	for (size_t k = 0; k < pfds_.size(); ++k)
	{
		if (pfds_[k].fd == this->nicks_it_->second)
		{
			victim_fd = (int)k;
			break;
		}
	}
	if (victim_fd != -1)
	{
		// std::cout << "AFTER KILL:\n";
		handle_quit(this->nicks_it_->second, victim_fd);
	}
	else
		std::cout << "handle_kill victim_fd not found\n";
}

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

void MiniIRCd::handle_who(const IRCMessage& msg, const int& fd)
{
	User& requester = users_.at(fd);
	if (msg.params.empty()) {
		sendLine(fd, ":miniircd 461 " + requester.nick + " WHO :Not enough parameters");
		return;
	}
	std::string chan = msg.params[0];
	if (chan[0] !=  '#') chan = "#" + chan;

	// std::map<std::string, std::vector<int> >::iterator it = chnl_members_.find(chan);
	this->chnl_mem_it_ = chnl_members_.find(chan);
	if (this->chnl_mem_it_ == chnl_members_.end()) {
		sendLine(fd, ":miniircd 403 " + requester.nick + " " + chan + " :No such channel");
		return;
	}
	const std::vector<int>& members = this->chnl_mem_it_->second;
	for (size_t k = 0; k < members.size(); ++k) {
		User& m = users_.at(members[k]);
		std::ostringstream reply;
		reply << ":miniircd 352 " << requester.nick << " " << chan << " ~" << m.user
			  << " " << "localhost miniircd " << m.nick
			  << " H :0 " << m.real;
		sendLine(fd, reply.str());
	}
	sendLine(fd, ":miniircd 315 " + requester.nick + " " + chan + " :End of WHO list");
}


bool MiniIRCd::handle_pass(const IRCMessage& msg, const int& fd, int i)
{
	if (msg.params.empty()) {
		sendLine(fd, "461 PASS :Not enough parameters");
		return false ;
	}
	std::string pw = msg.params[0];
	if (!pw.empty() && pw[0] == ':') pw = pw.substr(1);

	if (server_password_.empty()) {
		users_[fd].pass_ok = true;
		return true;
	}

	if (pw == server_password_) {
		users_[fd].pass_ok = true;
		return true;
	} else {
		sendLine(fd, "464 * :Password incorrect");
		handle_quit(fd, i);
		return false;
	}
}

void MiniIRCd::handle_oper(User& actual_user, const IRCMessage& msg)
{
	// Useless because IRSSI sets the nickname automatically:
	// if (!actual_user.nick.empty() && !actual_user.registered)
	// {
	// 	// ERR_NOTREGISTERED (451)
	// 	sendLine(actual_user.usr_fd, "451 * :You have not registered");
	// 	return ;
	// }

	if (msg.params.size() < 2)
	{
		// ERR_NEEDMOREPARAMS (461)
		sendLine(actual_user.usr_fd, "461 " + actual_user.nick + " OPER :Not enough parameters");
		return ;
	}

	if (msg.params[1] == this->oper_password_)
	{
		this->opers_[actual_user.usr_fd] = actual_user;
		// RPL_YOUREOPER (381)
		sendLine(actual_user.usr_fd, "381 " + actual_user.nick + " :You are now an IRC operator");
	}
	else
	{
		// ERR_PASSWDMISMATCH (464)
		sendLine(actual_user.usr_fd, "464 " + actual_user.nick + " :Password incorrect");
	}

}


void MiniIRCd::handle_mode(User& actual_user, IRCMessage msg)
{
	if (!this->channels_.empty())
	{
		this->chnls_it_ = this->channels_.find(*(msg.params.begin()));

		if (this->chnls_it_ != channels_.end())
		{
			// std::cout << "Channel \"" << this->chnls_it_->first << "\" found in Server \n";
			
			// Erasing channel name from msg.params
			std::rotate(msg.params.begin(), msg.params.begin() + 1, msg.params.end());
			msg.params.pop_back();
			
			bool res;
			std::string chnl_res;
			res = this->chnls_it_->second.channel_mode(msg.params, actual_user.nick, chnl_res);
			if (!res)
				sendLine(actual_user.usr_fd, chnl_res);
			else
			{
				// std::map<std::string, std::vector<int> >::iterator chnl_mem_it; 
				this->chnl_mem_it_ = this->chnl_members_.find(this->chnls_it_->second.get_chnl_name());
				if (this->chnl_mem_it_ != chnl_members_.end())
				{
					std::vector<int>& v = this->chnl_mem_it_->second;
					for (size_t k = 0; k < v.size(); ++k)
						sendLine(v[k], chnl_res);
				}
			}
		}
		else
		{
			std::string unfound_wrd = *(msg.params.begin());
			if (unfound_wrd.at(0) != '#')
				return ;
			// ERR_NOSUCHCHANNEL (403)
			std::string error_msg = "403 " + actual_user.nick + " " + *(msg.params.begin()) + " :No such channel";
			sendLine(actual_user.usr_fd, error_msg);
		}
	} // redundant 
	else
	{
		std::string unfound_wrd = *(msg.params.begin());
		if (unfound_wrd.at(0) != '#')
			return ;
		// ERR_NOSUCHCHANNEL (403)
		std::string error_msg = "403 " + actual_user.nick + " " + *(msg.params.begin()) + " :No such channel";
		sendLine(actual_user.usr_fd, error_msg);
	}
}

void MiniIRCd::handle_topic(const IRCMessage& msg, const int client_fd)
{
	// std::cout << "=> handle_topic, params: ";
	// std::cout << msg.params.size() << "\n";
	// if (msg.params.size() == 1)
	// 	std::cout << msg.params[0] << "\n";
	// std::cout << "=> handle_topic, trailing: "; 
	// std::cout << msg.trailing.size() << "\n";

	std::ostringstream os;
	std::ostringstream os_t;
	User u = users_.at(client_fd);

	if (msg.params.empty())
	{
		// std::cout << "TOPIC: ERR_NEEDMOREPARAMS (461)\n";
		
		// ERR_NEEDMOREPARAMS (461)
		// "<client> <command> :Not enough parameters"
		os << ":miniircd 461 ";
		os << u.nick << " ";
		os << "TOPIC :Not enough parameters";
		sendLine(client_fd, os.str());
		return ;
	}
	std::string chnl_name = msg.params[0];

	chnls_it_ = channels_.find(chnl_name);
	if (chnls_it_ == channels_.end())
	{
		// std::cout << "TOPIC: ERR_NOSUCHCHANNEL (403)\n";

		// ERR_NOSUCHCHANNEL (403)
		// "<client> <channel> :No such channel"
		os << ":miniircd 403 ";
		os << u.nick << " ";
		os << chnl_name;
		os << " :No such channel";
		sendLine(client_fd, os.str());
		return ;
	}
	
	Channel& c = chnls_it_->second;
	if (!c.is_chnl_usr(u.nick))
	{
		// std::cout << "TOPIC: ERR_NOTONCHANNEL (442)\n";

		// ERR_NOTONCHANNEL (442)
		// "<client> <channel> :You're not on that channel"
		os << ":miniircd 442 ";
		os << chnl_name;
		os << " :You're not on that channel";
		sendLine(client_fd, os.str());
		return ;
	}

	// only showing the topic
	if (msg.params.size() == 1 && msg.trailing.empty())
	{
		// std::cout << "TOPIC: Show topic\n";

		if (c.get_chnl_topic().empty())
		{

			// RPL_NOTOPIC (331)
			// "<client> <channel> :No topic is set"
			os << ":miniircd 331 ";
			os << u.nick << " ";
			os << chnl_name;
			os << " :No topic is set";
			sendLine(client_fd, os.str());
			return ;
		}
		else
		{
			// RPL_TOPIC (332)
			// "<client> <channel> :<topic>"
			os << ":miniircd 332 ";
			os << u.nick << " ";

			os << chnl_name << " :";
			os << c.get_chnl_topic();
			sendLine(client_fd, os.str());

			// RPL_TOPICWHOTIME (333)
			// "<client> <channel> <nick> <setat>"
			os_t << ":miniircd 333 ";
			os_t << u.nick << " ";

			os_t << c.get_chnl_topic_time();
			sendLine(client_fd, os_t.str());

			return ;
		}
	}
	else
	{
		// std::cout << "TOPIC: Change topic !\n";

		// changing topic and alerting all channel members
		// std::string new_topic = msg.trailing;

		if (!c.channel_topic(u.nick, msg.trailing, os))
		{
			sendLine(client_fd, os.str());
			return ;
		}

		// os << ":miniircd 332 ";
		// // "<client> <channel> :<topic>"
		// os << u.nick << " ";

		// os << chnl_name << " :";
		// os << c.get_chnl_topic();

		// :irc.example.com 333 nick #bar topic-setter 1487418032
		os_t << ":miniircd 333 ";
		os_t << u.nick << " ";
		// "<client> <channel> <nick> <setat>"
		os_t << c.get_chnl_topic_time();

		std::cout << "TOPIC CHANGED\n";
		std::cout << os.str() << "\n";
		std::cout << os_t.str() << "\n";

		std::vector<int> all_chnl_membs = chnl_members_.at(c.get_chnl_name());
		std::vector<int>::iterator membs_it = all_chnl_membs.begin();

		while (membs_it < all_chnl_membs.end())
		{
			sendLine(*membs_it, os.str());
			sendLine(*membs_it, os_t.str());
			membs_it++;
		}

	}
}


// KICK #channel user_C(,user_B,...) :reason to be kicked!
// IRSSI, will send KICK cmd to all users separately
void MiniIRCd::handle_kick(const IRCMessage& msg, const int kicker_fd)
{
	std::cout << "=> handle_kick:\n";

	std::ostringstream os;
	User kicker = users_.at(kicker_fd);

	if (msg.params.size() < 2)
	{
		std::cout << "ERR_NEEDMOREPARAMS (461)\n";
		//ERR_NEEDMOREPARAMS (461)
		// "<client> <command> :Not enough parameters"

		os << ":miniircd 461 ";
		os << kicker.nick;
		os << " KICK :Not enough parameters";
		sendLine(kicker_fd, os.str());
		return ;
	}
	
	std::cout << "msg.params[0] " << msg.params[0] << std::endl;
	std::cout << "msg.params[1] " << msg.params[1] << std::endl;
	if (!msg.trailing.empty())
		std::cout << "msg.trailing " << msg.trailing << std::endl;
	
	std::string target_chnl = msg.params[0];
	std::string target_usr = msg.params[1];

	// Valid channel?
	chnls_it_ = channels_.find(target_chnl);
	if (chnls_it_ == channels_.end())
	{
		std::cout << "ERR_NOSUCHCHANNEL (403)\n";
		// ERR_NOSUCHCHANNEL (403)
		// "<client> <channel> :No such channel"
		os << ":miniircd 403 ";
		os << kicker.nick << " ";
		os << target_chnl << " :No such channel";
		sendLine(kicker_fd, os.str()); 
		return ;
	}

	Channel& c = channels_.at(target_chnl);
	// Is the kicker on that channel?
	if (!c.is_chnl_usr(kicker.nick))
	{
		std::cout << "ERR_NOTONCHANNEL (442)\n";

		// ERR_NOTONCHANNEL (442)
		// "<client> <channel> :You're not on that channel"
		os << ":miniircd 442 ";
		os << kicker.nick << " ";
		os << target_chnl << " :You're not on that channel";
		sendLine(kicker_fd, os.str()); 
		return ;
	}

	// Is the kicker chanop?
	if (!c.is_chnl_op(kicker.nick))
	{
		std::cout << "ERR_CHANOPRIVSNEEDED (482)\n";
		
		// ERR_CHANOPRIVSNEEDED (482)
		// "<client> <channel> :You're not channel operator"
		os << ":miniircd 482 ";
		os << kicker.nick << " ";
		os << target_chnl << " :You're not channel operator";
		sendLine(kicker_fd, os.str()); 
		return ;
	}

	// Does the target nick exist?
	nicks_it_ = nick_map_.find(target_usr);
	if (nicks_it_ == nick_map_.end())
	{
		std::cout << "ERR_NOSUCHNICK (401)\n";

		// ERR_NOSUCHNICK (401)
		// "<client> <nickname> :No such nick/channel"
		os << ":miniircd 401 ";
		os << kicker.nick << " ";
		os << target_usr;
		os << " :No such nick/channel";
		sendLine(kicker_fd, os.str());
		return ;
	}

	// Is the target in the channel?
	if (!c.is_chnl_usr(target_usr))
	{
		std::cout << "ERR_USERNOTINCHANNEL (441)\n";

		// ERR_USERNOTINCHANNEL (441)
		// "<client> <nick> <channel> :They aren't on that channel"
		os << ":miniircd 441 ";
		os << kicker.nick << " ";
		os << target_usr << " ";
		os << target_chnl << " :They aren't on that channel";
		sendLine(kicker_fd, os.str());
		return ;
	}

	// :dan!d@localhost KICK #Melbourne alice :dan
	// message sent to all channel members:
	os << ":" << kicker.get_host_mask();
	os << " KICK " << target_chnl << " ";
	os << target_usr << " :";
	if (msg.trailing.empty())
		os << target_usr;
	else
	 	os << msg.trailing;

	std::vector<int> all_chnl_members = chnl_members_.at(target_chnl);
	std::vector<int>::iterator m_fd = all_chnl_members.begin();

	int counter = 0;
	while (m_fd != all_chnl_members.end())
	{
		counter++;
		sendLine(*m_fd, os.str());
		m_fd++;
	}
	std::cout << "KICKING MSG:\n" << os.str()
		<< "sent to " << counter << " users of " << c.get_chnl_name()
		<< "\n";

	c.channel_part(target_usr);
}

void MiniIRCd::handle_invite(const IRCMessage& msg, const int inviter_fd)
{
	if (msg.params.size() == 1)
	{
		// ERR_NEEDMOREPARAMS (461)
		// std::cout << "INVITE ERROR 461\n";
		sendLine(inviter_fd, ":miniircd 461 INVITE :Not enough parameters");
		return ;
	}

	nicks_it_ = nick_map_.find(msg.params[0]);
	if (msg.params.size() > 2 || nicks_it_ == nick_map_.end())
	{
		// std::cout << "INVITE ERROR no such user/ too many params\n";
		return ;
	}

	chnls_it_ = channels_.find(msg.params[1]);
	if (chnls_it_ == channels_.end())
	{
		// ERR_NOSUCHCHANNEL (403)
		// std::cout << "INVITE ERROR 403\n";

		sendLine(inviter_fd, ":miniircd 403 " + msg.params[1] + " :No such channel");
		return ;
	}

	Channel& c = chnls_it_->second;
    if (!c.is_chnl_usr(users_.at(inviter_fd).nick))
	{
		// std::cout << "INVITE ERROR 442\n";

		// ERR_NOTONCHANNEL (442)
		//  "<client> <channel> :You're not on that channel"
		sendLine(inviter_fd, ":miniircd 442 " + msg.params[0] + " " + c.get_chnl_name() + " :You're not on that channel");
		return ;
	}

	if (!c.is_chnl_op(users_.at(inviter_fd).nick))
	{
		// std::cout << "INVITE ERROR 482\n";

		// ERR_CHANOPRIVSNEEDED (482)
		// "<client> <channel> :You're not channel operator"
		sendLine(inviter_fd, ":miniircd 482 " + msg.params[1] + " :You're not channel operator");
		return ;
	}

	if (c.is_chnl_usr(msg.params[0]))
	{
		// std::cout << "INVITE ERROR 443\n";

		// ERR_USERONCHANNEL (443)
		// "<client> <nick> <channel> :is already on channel"
		sendLine(inviter_fd, ":miniircd 443 " + msg.params[0] + " " + msg.params[1] + " :is already on channel");
		return ;
	}

	c.channel_invite(msg.params[0]);

	// RPL_INVITING (341)
	// "<client> <nick> <channel>"

	User inviter = users_.at(inviter_fd);
	int invited_fd = nick_map_.at(msg.params[0]);
	User invited = users_.at(invited_fd);

	std::ostringstream os;
	os << ":" << inviter.get_host_mask();
	os << " INVITE ";
	os << invited.nick << " ";
	os << msg.params[1] << " ";
	sendLine(invited_fd, os.str());
	
	os.str("");
	os.clear();

	os << ":miniircd ";
	os << "341 ";
	os << inviter.nick << " ";
	os << msg.params[0] << " ";
	os << msg.params[1];
	sendLine(inviter_fd, os.str());
	return ;
}



int MiniIRCd::run()
{
	nick_map_.clear();

	//SIGNAL PROTECTION
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);



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

	
	while (!shutdown)
	{
		//if incoming connection, poll[0].revents will be set to POLLIN
		int rc = poll(&pfds_[0], pfds_.size(), -1);
		if (rc < 0)
		{
			if (errno == EINTR) {
				if (shutdown) break;
				continue;
			}
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
					User usr = users_.at(client_fd);
					std::string quitmsg = (usr.registered ? usr.nick : std::string("guest")) + " has quit";
					
					// erase the fd of the user who quitted the server
					// from each channel :
					for (this->chnl_mem_it_ = chnl_members_.begin(); this->chnl_mem_it_ != chnl_members_.end(); ++this->chnl_mem_it_)
					{
						std::vector<int> channel_fds = this->chnl_mem_it_->second;
						for (size_t k = 0; k < channel_fds.size(); ++k)
						{
							if (channel_fds[k] == client_fd)
								continue;
							// tell other users of this channel, that smbdy has quit :
							std::ostringstream os;
							os << ":" << usr.get_host_mask() << " QUIT :" << quitmsg;
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
					this->usr_it_ = opers_.find(client_fd);
					if (this->usr_it_ != opers_.end())
						opers_.erase(client_fd);
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
						} else if (cmd == "CAP") {
							handle_cap(msg, client_fd);
						} else if (cmd == "PASS")
						{
							if (!handle_pass(msg, client_fd, i))
								break ;
						} else if (cmd == "NICK")
						{
							// Test in case of wrong PSWD -> the user has quit
							// but IRSSI tries to register with /nick and /user
							// Also, the client retries several /nick commands
							// even after registration, so :
							
							// this->usr_it_ = this->users_.find(client_fd);
							// if (this->usr_it_ != this->users_.end()
							// 	&& !this->usr_it_->second.registered)
								handle_nick(msg, client_fd);
							// else
							//  	break ;
						} else if (cmd == "USER") {
							// Test in case of wrong PSWD -> the user has quit
							// but IRSSI tries to register with /nick and /user anyway,
							// so those verifications help 
							
							// this->usr_it_ = this->users_.find(client_fd);
							// if (this->usr_it_ == this->users_.end()
							// 	&& !this->usr_it_->second.registered)
								handle_user(msg, client_fd);
							// else
							//  	break;
						} else if (cmd == "OPER") {
							handle_oper(actual_user, msg);
						} else if (cmd == "JOIN") {
						// /!\ Join should handle several channels with eventual pswds
						// example : JOIN #channel,#channel2 pswd,pswd2(or nothing as pswd)
						// https://modern.ircdocs.horse/#join-message 
						// How to handle it inside IRCMessage?
							handle_join(msg, client_fd);
						} else if (cmd == "PART") {
							handle_part(msg, client_fd);
						} else if (cmd == "WHO") {
							handle_who(msg, client_fd);
						} else if (cmd == "WHOIS") {
							std::ostringstream os;
							usr_it_ = users_.find(client_fd);
							if (usr_it_ == users_.end())
							{
								// ERR_NOSUCHNICK (401) 
								std::cout << "Réponse négative à WHOIS:\n";
								os << ":miniircd 401 ";
								os << msg.params[0];
								os << " :No such nick/channel";
								sendLine(client_fd, os.str());
								std::cout << os.str() << std::endl;

								os.str("");
								os.clear();
							}
							else
							{
								std::cout << "Réponse à WHOIS:\n";
								// RPL_WHOISREGNICK (307)
								os << ":miniircd 3O7 " << msg.params[0] << " :has identified for this nick";
								sendLine(client_fd, os.str());
								std::cout << os.str() << std::endl;

								os.str("");
								os.clear();

								// RPL_ENDOFWHOIS (318)
								os << ":miniircd 318 ";
								os << msg.params[0];
								os << " :End of /WHOIS list";
								sendLine(client_fd, os.str());
								std::cout << os.str() << std::endl;

								os.str("");
								os.clear();
							} 

						} else if (cmd == "PRIVMSG") {
							handle_privmsg(msg, client_fd);
						} else if (cmd == "MODE") {
						// MODE can also be called on users 
						// we should ignore it.
						// ex : "MODE dan +i" = Setting the "invisible" user mode on dan.
						
						// in handle_mode() params :
						// I am using an instance of User instead of just his fd (client_fd).
						// Beacause I will need client's fd to send him replies from the server(sendLine),
						// and in each Channel, users are stored by their names : the Channel
						// will need to print their names and send to other users, know who is invited...						
							handle_mode(actual_user, msg);
						} else if (cmd == "TOPIC") {
							handle_topic(msg, client_fd);
						} else if (cmd == "INVITE") {
							handle_invite(msg, client_fd);
						} else if (cmd == "KICK") {
							handle_kick(msg, client_fd);
						} else if (cmd == "QUIT") {
							handle_quit(client_fd, i);
							std::cout << "quit break\n";
							break;
						} else if (cmd == "KILL") {
							handle_kill(client_fd, msg);
							std::cout << "kill break, killer fd :" << client_fd << "\n";
							break;
						} else {
							sendLine(client_fd, std::string(":miniircd NOTICE * :Unknown command ") + cmd);
						}
					}
					// end processing lines
				}
			} // end POLLIN
			if (re & POLLOUT)
			{
				flush_outgoing(i);

			}
		} // end clients loop
	} // main loop
	close(listenfd_);
	return 0;
}