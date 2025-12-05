/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:52:54 by dgerhard          #+#    #+#             */
/*   Updated: 2025/11/30 09:37:35 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniIRCd.hpp"
#include <iostream>
#include <stdexcept>

void parseArgs(const std::string port, const std::string password)
{
	if (port.find_first_not_of("0123456789") != std::string::npos)
		throw std::runtime_error("Port must only be numbers");

	int p = std::atoi(port.c_str());
	if (!(p > 0 && p <= 65535))
		throw std::runtime_error("Port must be between 1 and 65535");
	// I think we should start our range of accepted ports from 1025
	// because the range 0-1024 is reserved and since we are not root
	// on 42 PC's we probably could not use them :
	// https://serverfault.com/questions/241424/tcp-port-1023-or-tcp-port-1024-for-inbound-passive-ftp-traffic

	for (size_t i = 0; i < password.size(); ++i) {
		unsigned char ch = static_cast<unsigned char>(password[i]);
		if (!((ch >= ' ' && ch <= 'Z') || (ch >= 'a' && ch <= '~')))
			throw std::runtime_error("Password not composed of letters/numbers/symbols");
	}
	if (password.size() > 512)
		throw std::runtime_error("Password too long, 512 chars max");
}

int main(int argc, char** argv)
{
	std::string port = "";
	std::string password = "";

	try {
		if (argc != 3)
			throw std::runtime_error("Excpected input: port password");
		parseArgs(argv[1], argv[2]);
	} catch (std::exception& e)
	{
		std::cout << "Error: " << e.what() << '\n';
		return 1;
	}
	// I think we should use if/else instead of try/catch here, because :
	// https://stackoverflow.com/questions/651619/what-is-the-advantage-of-using-try-catch-versus-if-else
	// From what I understood, try/catch is useful when there is a running
	// process, and at a certain time an error can occur (like a server goes down)
	// but we don't know when exactly.
	// Or if catching an exception means we don't interrupt a process...
	// Wheras, in our main, we know that our errors are argv != 3, or 
	// other chars than "0123..." in the argv[1], or errors in argv[2],
	// and each of these errors should stop our programm. 

	port = argv[1];
	password = argv[2];
	MiniIRCd s(port, password);
	return s.run();
}