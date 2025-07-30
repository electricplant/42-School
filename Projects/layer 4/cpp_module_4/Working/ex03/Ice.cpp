/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:27:09 by dgerhard          #+#    #+#             */
/*   Updated: 2025/07/23 09:34:12 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"

Ice::Ice(std::string type) : AMateria(type)
{
	std::cout << "Default constructor Ice called" << std::endl;
}

AMateria* Ice::clone() const
{
	std::cout << "Ice copy (clone) constructor called" << std::endl;
	return new Ice(*this);
}

Ice::~Ice()
{
	std::cout << "Destructor Ice called" << std::endl;
}