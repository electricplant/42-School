/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:31:52 by dgerhard          #+#    #+#             */
/*   Updated: 2025/07/21 09:53:36 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include "Point.hpp"

Point::Point()
	: x(0), y(0)
{}

Point::Point(const float fx, const float fy)
	: x(fx), y(fy)
{}

Point::Point(const Point& other)
	: x(other.x), y(other.y)
{}

Point& Point::operator=(const Point& other)
{
	if (this != &other)
	{
		new (this)Point(other.getX().toFloat(), other.getY().toFloat());
	}
	return *this;

}

Fixed Point::getX() const
{
	return this->x;
}

Fixed Point::getY() const
{
	return this->y;
}

Point::~Point()
{}