/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:52:54 by dgerhard          #+#    #+#             */
/*   Updated: 2025/12/04 12:39:03 by dgerhard         ###   ########.fr       */
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

	if (argc != 3)
	{
		std::cout << "Excpected input: port password\n";
		return 1;
	}
	parseArgs(argv[1], argv[2]);

	port = argv[1];
	password = argv[2];
	MiniIRCd s(port, password);
	return s.run();
}