/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MiniIRCd.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:53:18 by dgerhard          #+#    #+#             */
/*   Updated: 2025/11/22 10:19:32 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <map>
#include <vector>

struct IRCMessage;

struct Client {
	int fd;
	std::string nick;
	std::string user;
	std::string real;
	bool registered;
	std::string inbuf;
	Client(): fd(-1), registered(false) {}
};

class MiniIRCd {
public:
	MiniIRCd(const std::string& port);
	~MiniIRCd();
	int run(); // blocking run loop, returns 0 on clean exit

private:
	std::string port_;
	int listenfd_;
	std::map<int, Client> clients_;
	std::map<std::string, int> nick_map_;
	std::map<std::string, std::vector<int> > channels_;

	int make_listen();
	void handle_ping(const IRCMessage& msg, const int& fd, const std::string& line);
	void handle_nick(const IRCMessage& msg, const int& fd);
	void handle_user(const IRCMessage& msg, const int& fd);
	void handle_join(const IRCMessage& msg, const int& fd);
	void handle_privmsg(const IRCMessage& msg, const int& fd);
	void handle_quit(const int& fd, std::vector<struct pollfd>& pfds, int i);

};
