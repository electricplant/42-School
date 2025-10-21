/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 09:57:34 by dgerhard          #+#    #+#             */
/*   Updated: 2025/10/21 10:49:16 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <ctime>

int main(void)
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	for (int i = 0; i < 10; i++)
	{
		Base* test = Base::generate();
		std::cout << "Test " << i + 1 << ": ";
		std::cout << "Pointer identifies as: ";
		Base::identify(test);
		std::cout << "Reference identifies as: ";
		Base::identify(*test);
		std::cout << "----------------------" << std::endl;
		delete test;
	}

	std::cout << "\nTesting null pointer: " << std::endl;
	Base::identify(NULL);

	std::cout << "\nTesting invalid reference: " << std::endl;
	A fake_a;
	Base& ref_base = fake_a;
	Base::identify(ref_base);
}