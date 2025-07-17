/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:17:03 by dgerhard          #+#    #+#             */
/*   Updated: 2025/07/17 09:14:02 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

void Harl::debug(void)
{
	std::cout << "[ DEBUG ]" << std::endl;
	std::cout << "This pasta is tasty" << std::endl << std::endl;
}

void Harl::info(void)
{
	std::cout << "[ INFO ]" << std::endl;
	std::cout << "This bowl does not seem very sturdy" << std::endl << std::endl; 
}

void Harl::warning(void)
{
	std::cout << "[ WARNING ]" << std::endl;
	std::cout << "The bowl appears to have a crack in it" << std::endl << std::endl;
}

void Harl::error(void)
{
	std::cout << "[ ERROR ]" << std::endl;
	std::cout << "The bowl has completely split in half and pasta is everywhere" << std::endl << std::endl;
}

void Harl::complain(std::string level)
{
	std::string levels[] = {"NONE", "DEBUG", "INFO", "WARNING"};
	Level level_code = NONE;

	//unfinished

	for (int i = 1; i <= ERROR; i++)
	{
		if (level == levels[i])
		{
			level_code = static_cast<Level>(i);
			break;
		}
	}

	switch (level_code)
	{
		case DEBUG:
			debug(); // fall through
		case INFO:
			info(); // fall through
		case WARNING:
			warning(); // fall through
		case ERROR:
			error();
			break;
		default:
			std::cout << "[ mindless mutterings ]" << std::endl;
			break;
	}
}