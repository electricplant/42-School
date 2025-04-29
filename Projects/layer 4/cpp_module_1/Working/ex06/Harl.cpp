/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:17:03 by dgerhard          #+#    #+#             */
/*   Updated: 2025/04/28 11:00:42 by dgerhard         ###   ########.fr       */
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
	Level level_code = NONE;

	if (level == "DEBUG")
		level_code = DEBUG;
	else if (level == "INFO")
		level_code = INFO;
	else if (level == "WARNING")
		level_code = WARNING;
	else if (level == "ERROR")
		level_code = ERROR;

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