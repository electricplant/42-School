/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:19:04 by dgerhard          #+#    #+#             */
/*   Updated: 2025/07/21 10:26:50 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include "Point.hpp"
#include <iostream>

bool bsp( Point const a, Point const b, Point const c, Point const point);

int main(void)
{
	Point a(10,10);
	Point b(0,0);
	Point c(5,0);
	Point point(3,1);

	if (bsp(a,b,c,point) == true)
		std::cout << "Point inside triangle" << std::endl;
	else
		std::cout << "Point outside triangle" << std::endl;
	
	return 0;
}