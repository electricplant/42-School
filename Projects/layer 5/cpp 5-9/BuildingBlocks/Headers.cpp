/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Headers.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 08:35:06 by dgerhard          #+#    #+#             */
/*   Updated: 2025/11/07 10:09:45 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Headers.hpp"

ClassName::ClassName() { }; //empty default constructor

ClassName::ClassName(const ClassName& other) //default copy constructor
{
	*this = other;
}

ClassName& ClassName::operator=(const ClassName& other)
{
	if (this != &other)
	{
		// _dataThing = other._dataThing;
	}
	return *this;
}

std::ostream& operator<<(std::ostream& os, const ClassName classname)
{
	os << classname.doThing() << /*whatever else*/ std::endl;
	return os;
}