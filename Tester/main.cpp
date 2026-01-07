/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCParser.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:02:00 by dgerhard          #+#    #+#             */
/*   Updated: 2025/11/18 16:06:53 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Working/IRCParser.hpp"
#include <cassert>
#include <iostream>

void test_simple_privmsg() {
	IRCMessage m = parseLine(":nick!user@host PRIVMSG #chan :Hello there");
	assert(m.prefix == "nick!user@host");
	assert(m.command == "PRIVMSG");
	assert(m.params.size() == 1 && m.params[0] == "#chan");
	assert(m.trailing == "Hello there");
}

void test_ping() {
	IRCMessage m = parseLine("PING :server");
	assert(m.prefix.empty());
	assert(m.command == "PING");
	assert(m.trailing == "server");
}

void test_numeric_and_params() {
	IRCMessage m = parseLine(":server 353 nick = #chan :nick1 nick2");
	assert(m.command == "353");
	assert(m.params.size() >= 3);
	assert(m.trailing == "nick1 nick2");
}

int main() {
	test_simple_privmsg();
	test_ping();
	test_numeric_and_params();
	std::cout << "parser tests passed\n";
	return 0;
}