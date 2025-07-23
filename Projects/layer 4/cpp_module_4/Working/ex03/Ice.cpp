/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:27:09 by dgerhard          #+#    #+#             */
/*   Updated: 2025/07/23 07:30:22 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"

Ice::Ice(std::string type) : AMateria(type)
{
	std::cout << "Default constructor Ice called" << std::endl;
}

Ice::~Ice()
{
	std::cout << "Destructor Ice called" << std::endl;
}