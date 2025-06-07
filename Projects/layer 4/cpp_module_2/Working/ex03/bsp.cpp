/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:54:00 by dgerhard          #+#    #+#             */
/*   Updated: 2025/05/19 19:30:17 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include "Point.hpp"
#include <iostream>

bool bsp( Point const a, Point const b, Point const c, Point const point)
{
	std::cout << "a.x = " << a.getX() << std::endl;
	std::cout << "a.y = " << a.getY() << std::endl;
	std::cout << "b.x = " << b.getX() << std::endl;
	std::cout << "b.y = " << b.getY() << std::endl;
	std::cout << "c.x = " << c.getX() << std::endl;
	std::cout << "c.y = " << c.getY() << std::endl;

	std::cout << "point.x = " << point.getX() << std::endl;
	std::cout << "point.y = " << point.getY() << std::endl;
	

	//returns true if point is inside triangle, false otherwise
	//if on edge or vertex, return false
	return true;
}