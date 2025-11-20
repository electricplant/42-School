/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:52:54 by dgerhard          #+#    #+#             */
/*   Updated: 2025/11/18 16:03:40 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniIRCd.hpp"
#include <iostream>

int main(int argc, char** argv)
{
	std::string port = "6667"; //change this to require a password
	if (argc >= 2) port = argv[1]; //redo this with argc != 3
	MiniIRCd s(port);
	return s.run();
}