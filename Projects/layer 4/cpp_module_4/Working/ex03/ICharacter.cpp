/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ICharacter.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:31:00 by dgerhard          #+#    #+#             */
/*   Updated: 2025/07/23 09:35:08 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ICharacter.hpp"

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