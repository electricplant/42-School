/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:48:59 by dgerhard          #+#    #+#             */
/*   Updated: 2025/06/08 08:52:39 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "FragTrap.hpp"

FragTrap::FragTrap(std::string name) : ClapTrap(name)
{
	this->health = 100;
	this->energy = 100;
	this->damage = 30;
	std::cout << "FragTrap " << this->name << " constructor called" << std::endl;
}

void FragTrap::highFivesGuys(void)
{
	if (this->energy > 0)
	{
		std::cout << "FragTrap " << this->name << " wants a High-Five!" << std::endl;
		this->energy--;
	}
	else
	{
		std::cout << "FragTrap" << this->name << " has no energy" << std::endl;
	}
}

FragTrap::~FragTrap()
{
	std::cout << "FragTrap " << this->name << " Destructor called" << std::endl;
}