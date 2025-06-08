/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 10:17:41 by dgerhard          #+#    #+#             */
/*   Updated: 2025/06/08 10:26:11 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap(std::string name) :
	ClapTrap(name + "_clap_name"),
	ScavTrap(name),
	FragTrap(name)
{
	this->name = name;
	this->health = FragTrap::health;
	this->energy = ScavTrap::energy;
	this->damage = FragTrap::damage;
	std::cout << "DiamondTrap " << this->name << " constructor called" << std::endl;
}

void DiamondTrap::whoAmI()
{
	std::cout << "I am DiamondTrap " << this->name << " and my ClapTrap name is " 
				<< ClapTrap::name << std::endl;
}

DiamondTrap::~DiamondTrap()
{
	std::cout << "DiamondTrap " << this->name << " Destructor called" << std::endl;
}