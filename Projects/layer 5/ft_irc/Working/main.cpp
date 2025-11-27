/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:52:54 by dgerhard          #+#    #+#             */
/*   Updated: 2025/11/27 08:53:21 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniIRCd.hpp"
#include <iostream>

int main(int argc, char** argv)
{
	std::string port = "6667";
	std::string password = "";
	if (argc >= 2) port = argv[1];
	if (argc >= 3) password = argv[2];
	MiniIRCd s(port, password);
	return s.run();
}