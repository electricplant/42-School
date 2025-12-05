/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MiniIRCd.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:53:18 by dgerhard          #+#    #+#             */
/*   Updated: 2025/11/29 09:04:08 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <map>
#include <vector>
#include <iomanip>
#include <sstream>
#include <algorithm>

struct IRCMessage;
class Channel;


struct Client {
	int fd;
	std::string nick;
	std::string user;
	std::string real;
	bool registered;
	bool pass_ok;
	std::string inbuf;
	std::string outbuf;
	Client(): fd(-1), registered(false), pass_ok(false) {}
};

class MiniIRCd {
public:
	MiniIRCd(const std::string& port, const std::string& password = " ");
	~MiniIRCd();
	int run(); // blocking run loop, returns 0 on clean exit

private:
	std::string port_;
	std::string server_password_;
	int listenfd_;
	std::map<int, Client> clients_;
	std::map<std::string, int> nick_map_;
	// std::map<std::string, std::vector<int> > channels_;
	std::vector<struct pollfd> pfds_;

	int find_pollfd_index(int fd);
	void flush_outgoing(int idx);
	void sendLine(int fd, const std::string& line);
	void send_numeric(int fd, const std::string& target, int code, const std::string& msg);

	int make_listen();
	void handle_ping(const IRCMessage& msg, const int& fd);
	void handle_pass(const IRCMessage& msg, const int& fd, std::vector<struct pollfd>& pfds, int i);
	void handle_nick(const IRCMessage& msg, const int& fd);
	void handle_user(const IRCMessage& msg, const int& fd);
	void handle_join(const IRCMessage& msg, const int& fd);
	void handle_privmsg(const IRCMessage& msg, const int& fd);
	void handle_quit(const int& fd, std::vector<struct pollfd>& pfds, int i);
	void handle_cap(const IRCMessage& msg, const int& fd);

	std::map<std::string, Channel*> channels_;
};

#include "Channel.hpp"
