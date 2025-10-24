/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:24:30 by dgerhard          #+#    #+#             */
/*   Updated: 2025/10/24 13:44:34 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "iter.hpp"

void print(int x)
{
	std::cout << x << " ";
}

void modify(int &x)
{
	x += 1;
}

void printRef(const int& x)
{
	std::cout << x << " ";
}

int main()
{
	int array[] = {9, 3, 1, 0, 3};
	iter(array, 5, print);
	std::cout << std::endl;
	
	iter(array, 5, modify);

	iter(array, 5, printRef);
	std::cout << std::endl;
	
	return 0;
}