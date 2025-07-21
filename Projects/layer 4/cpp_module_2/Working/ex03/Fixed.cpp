/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:58:11 by dgerhard          #+#    #+#             */
/*   Updated: 2025/07/21 09:50:06 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <iostream>
#include <cmath>

Fixed::Fixed() : num(0)
{
	// std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const int value)
{
	// std::cout << "Int constructor called" << std::endl;
	this->num = value << this->frac;
}

Fixed::Fixed(const float value)
{
	// std::cout << "Float constructor called" << std::endl;
	this->num = roundf(value * (1 << this->frac));
}

Fixed::Fixed(const Fixed& other)
{
	// std::cout << "Copy constructor called" << std::endl;
	*this = other;
}

Fixed& Fixed::operator=(const Fixed& other)
{
	// std::cout << "Copy assignment operator called" << std::endl;
	if (this != &other)
		this->num = other.getRawBits();
	return *this;
}

bool Fixed::operator==(const Fixed& other) const
{
	return this->num == other.getRawBits();
}

bool Fixed::operator!=(const Fixed& other) const
{
	return this->num != other.getRawBits();
}

bool Fixed::operator<=(const Fixed& other) const
{
	return this->num <= other.getRawBits();
}

bool Fixed::operator>=(const Fixed& other) const
{
	return this->num >= other.getRawBits();
}

bool Fixed::operator<(const Fixed& other) const
{
	return this->num < other.getRawBits();
}

bool Fixed::operator>(const Fixed& other) const
{
	return this->num > other.getRawBits();
}

Fixed Fixed::operator+(const Fixed& other) const
{
	Fixed result;
	result.setRawBits(this->num + other.getRawBits());
	return result;
}

Fixed Fixed::operator-(const Fixed& other) const
{
	Fixed result;
	result.setRawBits(this->num - other.getRawBits());
	return result;
}

Fixed Fixed::operator*(const Fixed& other) const
{
	Fixed result;
	result.setRawBits(this->num * other.getRawBits() >> this->frac);
	return result;
}

Fixed Fixed::operator/(const Fixed& other) const
{
	Fixed result;
	result.setRawBits(((int64_t)this->num << this->frac) / other.getRawBits());
	return result;
}

Fixed& Fixed::operator++()
{
	this->num++;
	return *this;
}

Fixed Fixed::operator++(int)
{
	Fixed temp(*this);
	this->num++;
	return temp;
}

Fixed& Fixed::operator--()
{
	this->num--;
	return *this;
}

Fixed Fixed::operator--(int)
{
	Fixed temp(*this);
	this->num++;
	return temp;
}

Fixed& Fixed::min(Fixed& one, Fixed& two)
{
	if (one.getRawBits() > two.getRawBits())
		return two;
	return one;
}

const Fixed& Fixed::min(const Fixed& one, const Fixed& two)
{
	if (one.getRawBits() > two.getRawBits())
		return two;
	return one;
}

Fixed& Fixed::max(Fixed& one, Fixed& two)
{
	if (one.getRawBits() > two.getRawBits())
		return one;
	return two;
}

const Fixed& Fixed::max(const Fixed& one, const Fixed& two)
{
	if (one.getRawBits() > two.getRawBits())
		return one;
	return two;
}

float Fixed::toFloat(void) const
{
	return (float)this->num / (1 << this->frac);
}

int Fixed::toInt(void) const
{
	return this->num >> this->frac;
}

int Fixed::getRawBits(void) const
{
	return this->num;
}

void Fixed::setRawBits(int const raw)
{
	this->num = raw;
}

Fixed::~Fixed()
{
	// std::cout << "Destructor called" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Fixed& fixed)
{
	os << fixed.toFloat();
	return os;
}