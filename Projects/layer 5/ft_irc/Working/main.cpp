/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:52:54 by dgerhard          #+#    #+#             */
/*   Updated: 2025/11/28 07:57:29 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniIRCd.hpp"
#include <iostream>

int main(int argc, char** argv)
{
	std::string port = "6667";
	std::string password = "";
	if (argc != 3){
		std::cout << "Expected input: port password\n";
		return 1;
	}
	port = argv[1]; //I should add a bit of parsing to make sure it's just numbers.
	password = argv[2];
	MiniIRCd s(port, password);
	return s.run();
}