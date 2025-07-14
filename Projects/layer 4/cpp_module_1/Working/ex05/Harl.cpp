/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:17:03 by dgerhard          #+#    #+#             */
/*   Updated: 2025/07/14 12:49:08 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

void Harl::debug(void)
{
	std::cout << "This pasta is tasty" << std::endl;
}

void Harl::info(void)
{
	std::cout << "This bowl does not seem very sturdy" << std::endl; 
}

void Harl::warning(void)
{
	std::cout << "The bowl appears to have a crack in it" << std::endl;
}

void Harl::error(void)
{
	std::cout << "The bowl has completely split in half and pasta is everywhere" << std::endl;
}

void Harl::complain(std::string level)
{
	void (Harl::*functionPointers[4])(void) = {
		&Harl::debug,
		&Harl::info,
		&Harl::warning,
		&Harl::error
	};

	std::string levels[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};

	for (int i = 0; i < 4; i++)
	{
		if (level == levels[i])
		{
			(this->*functionPointers[i])();
			return ;
		}
	}

	std::cout << "[ Who knows what it is this time ]" << std::endl; 
}