/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:27:21 by dgerhard          #+#    #+#             */
/*   Updated: 2025/07/23 07:29:26 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"

Cure::Cure(std::string type) : AMateria(type)
{
	std::cout << "Default constructor Cure called" << std::endl;
}

Cure::~Cure()
{
	std::cout << "Destructor Cure called" << std::endl;
}