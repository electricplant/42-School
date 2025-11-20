/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MiniIRCd.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:53:18 by dgerhard          #+#    #+#             */
/*   Updated: 2025/11/19 06:50:06 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <map>
#include <vector>

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
};
