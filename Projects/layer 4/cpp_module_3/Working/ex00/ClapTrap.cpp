/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:48:50 by dgerhard          #+#    #+#             */
/*   Updated: 2025/06/08 09:45:14 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap() : name("Nerd"), health(10), energy(10), damage(0)
{
	std::cout << "Default Constructor called" << std::endl;
}

ClapTrap::ClapTrap(const std::string name) : health(10), energy(10), damage(0)
{
	std::cout << "Constructor called" << std::endl;
	this->name = name;
}

void ClapTrap::attack(const std::string& target)
{
	if (this->health != 0)
	{
		std::cout << "Claptrap " << this->name << " attacks ";
		std::cout << target << ", causing " << this->damage;
		std::cout << " points of damage!" << std::endl;
		this->energy--;
		// std::cout << "Current energy: " << this->energy << std::endl;
	}
	else if (this->energy == 0)
	{
		std::cout << "Claptrap " << this->name << " is out of energy" << std::endl;
		// std::cout << "Current energy: " << this->energy << std::endl;
	}
	else
	{
		std::cout << "Claptrap " << this->name << " is dead" << std::endl;
		// std::cout << "Current energy: " << this->energy << std::endl;
	}

}

void ClapTrap::takeDamage(unsigned int amount)
{
	if (this->health > 0)
	{
		std::cout << "Claptrap " << this->name << " takes ";
		std::cout << amount << " points of damage!" << std::endl;
		if (amount >= this->health)
			this->health = 0;
		else
		{
			this->health -= amount;
			// std::cout << "Current health: " << this->health << std::endl;
		}
	}
	else
		std::cout << "Claptrap " << this->name << " is already dead" << std::endl;

}

void ClapTrap::beRepaired(unsigned int amount)
{
	if (this->health > 0)
	{
		if (this->energy > 0)
		{
			std::cout << "Claptrap " << this->name << " repairs ";
			std::cout << amount << " points of health!" << std::endl;
			this->energy--;
			this->health += amount;
		// std::cout << "Current energy: " << this->energy << std::endl;
		// std::cout << "Current health: " << this->health << std::endl;
		}
		else
		{
			std::cout << "Claptrap " << this->name << " is out of energy" << std::endl;
			// std::cout << "Current energy: " << this->energy << std::endl;
		}
	}
	else
	{
		std::cout << "Claptrap " << this->name << " is dead and cannot repair" << std::endl;
		// std::cout << "Current energy: " << this->energy << std::endl;
		// std::cout << "Current health: " << this->health << std::endl;
	}
}


ClapTrap::~ClapTrap()
{
	std::cout << "Destructor called" << std::endl;
}