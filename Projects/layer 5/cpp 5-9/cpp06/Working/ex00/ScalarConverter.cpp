/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:22:25 by dgerhard          #+#    #+#             */
/*   Updated: 2025/10/11 21:34:11 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

ScalarType getType(const std::string& input)
{
	size_t pos = input.find_first_not_of("0123456789+-.");
	
	if (input.find("inf") != std::string::npos || 
			input.find("nan") != std::string::npos) //We got that crap
	{
		return STUPID;
	}
	else if (pos != std::string::npos && input[pos] == 'f') //there's an 'f' at the end
	{
		return FLOAT;
	}
	else if (input.find('.') != std::string::npos) //there's a period somewhere
	{
		return DOUBLE;
	}
	else if (input.find_first_of("0123456789") != std::string::npos) //it's got numbers
	{
		return INT;
	}
	else 
	{
		return CHAR;
	}
}

void its_a_char(std::string input)
{
	std::cout << "char: " << input << std::endl;
	std::cout << "int: " << "impossible" << std::endl;
	std::cout << "float: " << "impossible" << std::endl;
	std::cout << "double: " << "impossible" << std::endl;
}

void its_an_int(std::string input)
{
	try {
		int num = atoi(input.c_str());
		std::cout << "char: ";
		if (num < 32 || num > 126)
			std::cout << "Non displayable" << std::endl;
		else
			std::cout << "'" << static_cast<char>(num) << "'" << std::endl;
		std::cout << "int: " << num << std::endl;
		std::cout << "float: " << static_cast<float>(num) << ".0f" << std::endl;
		std::cout << "double: " << static_cast<double>(num) << ".0" << std::endl;
	} catch (const std::exception& e)
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
	}
}

void its_a_float(std::string input)
{
	try {
		float num = atof(input.c_str());
		std::cout << "char: ";
		if (num < 0 || num > 127)
			std::cout << "impossible" << std::endl;
		else if (num < 32 || num == 127)
			std::cout << "Non-displayable" << std::endl;
		else
			std::cout << "'" << static_cast<char>(num) << "'" << std::endl;
		std::cout << "int: " << static_cast<int>(num) << std::endl;
		std::cout << "float: " << num << ".0f" << std::endl;
		std::cout << "double: " << static_cast<double>(num) << ".0" << std::endl;
	} catch (const std::exception& e)
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
	}
}

void its_a_double(std::string input)
{
	try {
		double num = atof(input.c_str());
		std::cout << "char: ";
		if (num < 0 || num > 127)
			std::cout << "impossible" << std::endl;
		else if (num < 32 || num == 127)
			std::cout << "Non-displayable" << std::endl;
		else
			std::cout << "'" << static_cast<char>(num) << "'" << std::endl;
		std::cout << "int: " << static_cast<int>(num) << std::endl;
		std::cout << "float: " << static_cast<float>(num) << ".0f" << std::endl;
		std::cout << "double: " << num << ".0" << std::endl;
	} catch (const std::exception& e)
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
	}
}

void its_stupid(std::string input)
{
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	std::cout << "float: " << input << "f" << std::endl;
	std::cout << "double: " << input << std::endl;
}

void its_invalid(std::string input)
{
	std::cout << "invalid input" << std::endl;
}

void ScalarConverter::convert(const std::string& input)
{
	// int i;
	// char sign;
	char c;
	ScalarType VarType = INVALID;
	// i = 0;
	// sign = 0;
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

	
	// if (input[0] == '-' || input[0] == '+')
	// {
	// 	if (input[0] == '-')
	// 	sign = '-';
	// }
	
	VarType = getType(input);
	switch (VarType){
		case CHAR:
			its_a_char(input);
			break;
		case INT:
			its_an_int(input);
			break;
		case FLOAT:
			its_a_float(input);
			break;
		case DOUBLE:
			its_a_double(input);
			break;
		case STUPID:
			its_stupid(input);
			break;
		case INVALID:
			its_invalid(input);
			break;
	}	
}


const char* ScalarConverter::ConvertException::what() const throw()
{
	return "Conversion failed";
}
