/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 13:48:31 by dgerhard          #+#    #+#             */
/*   Updated: 2025/10/19 14:42:51 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Data.hpp"

Data::Data() : _size(10)
{
	std::cout << "default Constructor called" << std::endl;
}

Data::Data(Data const& other)
{
	std::cout << "Copy Constructor called" << std::endl;
	*this = other;
}

Data& Data::operator=(Data const &other)
{
		if (this != &other) {
		this->_size = other._size;
	}
	return *this;
}

Data::~Data()
{
	std::cout << "default Destructor called" << std::endl;
}

std::ostream &	operator<<(std::ostream & o, Data const &other) {
	o << other.getSize();
	return o;
}

int	Data::getSize() const {
	return this->_size;
}
