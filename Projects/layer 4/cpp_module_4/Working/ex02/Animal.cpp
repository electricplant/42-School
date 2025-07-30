/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:52:15 by dgerhard          #+#    #+#             */
/*   Updated: 2025/07/30 08:51:03 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal()
{
	std::cout << "Default Animal Const called" << std::endl;
}

Animal::Animal(const Animal& other)
{
	std::cout << "Animal copy constructor called" << std::endl;
	*this = other;
}

Animal& Animal::operator=(const Animal& other)
{
	std::cout << "Animal assignment operator called" << std::endl;
	this->type = other.type;
	return *this;
}

Animal::~Animal()
{
	std::cout << "Animal Dest called" << std::endl;
}

void Animal::makeSound() const
{
	std::cout << "quack" << std::endl;
}

std::string Animal::getType() const
{
	return(type);
}