/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 08:46:11 by dgerhard          #+#    #+#             */
/*   Updated: 2025/07/23 08:21:50 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"

AMateria::AMateria(std::string const& type)
{
	std::cout << "AMateria constructor called" << std::endl;
	this->type = type;
}

void AMateria::use(ICharacter& target)
{

}

const std::string& AMateria::getType() const
{
	return this->type;
}

AMateria::~AMateria()
{
	std::cout << "Destructor AMateria called" << std::endl;
}
