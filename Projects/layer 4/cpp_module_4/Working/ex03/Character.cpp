/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:31:00 by dgerhard          #+#    #+#             */
/*   Updated: 2025/07/22 11:59:25 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"

ICharacter::ICharacter()
{
	std::cout << "Default constructor called" << std::endl;
}

ICharacter::ICharacter(std::string name)
{
	std::cout << "Creating: " << name << std::endl;
	this->name = name;
}

ICharacter::~ICharacter()
{
	std::cout << "Destructor called" << std::endl;
}