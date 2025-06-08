/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:48:59 by dgerhard          #+#    #+#             */
/*   Updated: 2025/06/08 08:47:55 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "FragTrap.hpp"

FragTrap::FragTrap(std::string name) : ClapTrap(name)
{
	this->health = 100;
	this->energy = 100;
	this->damage = 30;
	std::cout << "FragTrap " << this->name << " created!" << std::endl;
}

void FragTrap::attack(const std::string& target)
{
	if (this->health != 0)
	{
		std::cout << "FragTrap " << this->name << " attacks ";
		std::cout << target << ", causing " << this->damage;
		std::cout << " points of damage!" << std::endl;
		this->energy--;
	}
	else if (this->energy == 0)
	{
		std::cout << "FragTrap " << this->name << " is out of energy" << std::endl;
	}
	else
	{
		std::cout << "FragTrap " << this->name << " is dead" << std::endl;
	}
}

void FragTrap::highFivesGuys(void)
{
	std::cout << "FragTrap " << this->name << "is high-fiving guys" << std::endl;
}

FragTrap::~FragTrap()
{
	std::cout << "FragTrap " << this->name << " Destructor called" << std::endl;
}