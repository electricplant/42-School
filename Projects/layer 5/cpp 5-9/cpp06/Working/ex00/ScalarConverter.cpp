/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:22:25 by dgerhard          #+#    #+#             */
/*   Updated: 2025/10/09 17:55:29 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

ScalarType getType(const std::string& input)
{
	size_t pos = input.find_first_not_of("0123456789+-.");
	
	if (input.find("inf") != std::string::npos || 
			input.find("nan") != std::string::npos) 
	{
		return STUPID;
	}
	else if (pos != std::string::npos && input[pos] == 'f')
	{
		return FLOAT;
	}
	else if (input.find(',') != std::string::npos)
	{
		return DOUBLE;
	}
	else if (input.find_first_of("0123456789") != std::string::npos)
	{
		return INT;
	}
	else 
	{
		return CHAR;
	}
}

void ScalarConverter::convert(const std::string& input)
{
	int i;
	char sign;
	char c;
	ScalarType VarType = INVALID;
	i = 0;
	sign = 0;
	c = 0;
	if (input.empty())
		return;

	if (input.length() == 3 && input[0] == '\'' && input[2] == '\'')
	{
		c = input[1];
		std::cout <<  "char: ";
		if (c < 32 || c >= 127)
		{
			std::cout << "non-printable" << std::endl;
		}
		else
		{
			std::cout << "'" << c << "'" << std::endl;
		}
		std::cout << "int: " << static_cast<int>(c) << std::endl;
		std::cout << "float: " << static_cast<float>(c) << ".0f" << std::endl;
		std::cout << "double: " << static_cast<double>(c) << ".0" << std::endl;
		return;
	}

	
	if (input[0] == '-' || input[0] == '+')
	{
		if (input[0] == '-')
		sign = '-';
	}
	
	VarType = getType(input);
	switch (VarType){
		case CHAR:
		
			break;
		case INT:

			break;
		case FLOAT:

			break;
		case DOUBLE:

			break;
		case STUPID:

			break;
		case INVALID:

			break;
	}	
}

const char* ScalarConverter::ConvertException::what() const throw()
{
	return "Conversion failed";
}
