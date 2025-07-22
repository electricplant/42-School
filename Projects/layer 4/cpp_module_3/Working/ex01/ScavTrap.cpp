/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:48:59 by dgerhard          #+#    #+#             */
/*   Updated: 2025/07/22 10:21:23 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

ScavTrap::ScavTrap(std::string name) : ClapTrap(name)
{
	this->health = 100;
	this->energy = 50;
	this->damage = 20;
	std::cout << "ScavTrap " << this->name << " constructor called" << std::endl;
}

void ScavTrap::attack(const std::string& target)
{
	if (this->health != 0)
	{
		std::cout << "ScavTrap " << this->name << " attacks ";
		std::cout << target << ", causing " << this->damage;
		std::cout << " points of damage!" << std::endl;
		this->energy--;
	}
	else if (this->energy == 0)
	{
		std::cout << "ScavTrap " << this->name << " is out of energy" << std::endl;
	}
	else
	{
		std::cout << "ScavTrap " << this->name << " is dead" << std::endl;
	}
}

void ScavTrap::guardGate()
{
	std::cout << "ScavTrap " << this->name << " is guarding the gate" << std::endl;
}

ScavTrap::~ScavTrap()
{
	std::cout << "ScavTrap " << this->name << " Destructor called" << std::endl;
}