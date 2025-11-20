/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCParser.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:57:34 by dgerhard          #+#    #+#             */
/*   Updated: 2025/11/18 16:07:03 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCParser.hpp"
#include <cstring>

IRCMessage parseLine(const std::string& line)
{
	IRCMessage msg;
	size_t i = 0, len = line.size();

	// prefix
	if (i < len && line[i] == ':') {
		++i;
		size_t sp = line.find(' ', i);
		if (sp == std::string::npos) return msg;
		msg.prefix = line.substr(i, sp - i);
		i = sp + 1;
	}

	// command
	while (i < len && line[i] == ' ') ++i;
	size_t sp = line.find(' ', i);
	if (sp == std::string::npos) {
		msg.command = line.substr(i);
		return msg;
	}
	msg.command = line.substr(i, sp - i);
	i = sp + 1;

	// params and trailing
	while (i < len) {
		if (line[i] == ':') {
			msg.trailing = line.substr(i + 1);
			break;
		}
		while (i < len && line[i] == ' ') ++i;
		size_t nsp = line.find(' ', i);
		if (nsp == std::string::npos) {
			if (i < len) msg.params.push_back(line.substr(i));
			break;
		} else {
			msg.params.push_back(line.substr(i, nsp - i));
			i = nsp + 1;
		}
	}
	return msg;
}