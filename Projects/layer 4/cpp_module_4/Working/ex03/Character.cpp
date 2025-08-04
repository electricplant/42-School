/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 09:38:57 by dgerhard          #+#    #+#             */
/*   Updated: 2025/07/23 09:45:07 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"

Character::Character(std::string name)
{
	std::cout << "Constructor Character called" << std::endl;
	this->name = name;
}

Character::~Character()
{
	std::cout << "Default destructor " << this->name << " destroyed" << std::endl;
}

std::string const& Character::getName() const
{
	return(this->name);
}

void Character::equip(AMateria* m)
{
	
}

void Character::unequip(int idx)
{
	
}

void Character::use(int idx, ICharacter& target)
{
	
}