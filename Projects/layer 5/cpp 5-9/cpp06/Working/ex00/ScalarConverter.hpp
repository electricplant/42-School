/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:22:27 by dgerhard          #+#    #+#             */
/*   Updated: 2025/11/12 06:43:47 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <limits.h>
#include <cfloat>

class ScalarConverter
{
	public:
		static void convert(const std::string input);

	class ConvertException: public std::exception
	{
		public:
			virtual const char* what() const throw();
	};
};
