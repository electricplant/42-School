/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:22:25 by dgerhard          #+#    #+#             */
/*   Updated: 2025/10/06 15:02:30 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() 
{
	std::cout << "Default constructor called" << std::endl;
}

ScalarConverter::ScalarConverter(const std::string& input)
: input(input)
{
}

ScalarConverter::ScalarConverter(const ScalarConverter& other)
: input(other.input)
{
	std::cout << "Copy constructor called" << std::endl;
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other)
{
	std::cout << "Copy assignment operator called" << std::endl;
	return *this;
}

ScalarConverter::~ScalarConverter()
{
	std::cout << "Default destructor called" << std::endl;
}

void ScalarConverter::convert(std::string input)
{
	//output char literals ex: 'c' 'a' (if not ASCII or printable, add message)
	//output int literals ex 0, -42, 42
	//output float literals ex: 0.0f, -4.2f, 4.2f
	//output double literals ex: 0.0, -4.2, 4.2
}

