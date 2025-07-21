/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:56:31 by dgerhard          #+#    #+#             */
/*   Updated: 2025/07/20 08:53:11 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat()
{
	std::cout << "Default Cat Const called" << std::endl;
	this->type = "Cat";
}

Cat::~Cat()
{
	std::cout << "Cat Dest called" << std::endl;
}

void Cat::makeSound() const
{
	std::cout << "Meow" << std::endl;
}