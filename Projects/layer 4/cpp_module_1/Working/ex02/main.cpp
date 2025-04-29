/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:03:10 by dgerhard          #+#    #+#             */
/*   Updated: 2025/04/26 13:27:49 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>

int	main(void)
{
	std::string	message = "HI THIS IS BRAIN";
	std::string* stringPTR = &message;
	std::string& stringREF = message;

	std::cout << "Memory addr of string: " << &message << std::endl;
	std::cout << "Memory addr held by stringPTR: " << stringPTR << std::endl;
	std::cout << "Memory addr held by stringREF: " << &stringREF << std::endl;

	std::cout << "\nValue of string: " << message << std::endl;
	std::cout << "Value pointed by stringPTR: " << *stringPTR << std::endl;
	std::cout << "Value pointed by stringREF: " << stringREF << std::endl;
}