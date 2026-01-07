/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCParser.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:55:03 by dgerhard          #+#    #+#             */
/*   Updated: 2025/11/18 15:56:35 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <vector>

struct IRCMessage
{
	std::string prefix;
	std::string command;
	std::vector<std::string> params;
	std::string trailing;
};

/* Parse a single IRC protocol line (without CRLF).
   Returns an IRCMessage with parsed fields. */
IRCMessage parseLine(const std::string& line);