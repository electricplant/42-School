/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 10:00:58 by dgerhard          #+#    #+#             */
/*   Updated: 2025/10/21 10:35:58 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

Base::~Base() {}

Base* Base::generate(void)
{
	static bool first = true;
	if (first)
	{
		srand(time(NULL));
		first = false;
	}

	switch (rand() % 3)
	{
		case 0: return new A();
		case 1: return new B();
		case 2: return new C();
		default: return NULL;

	}
}

void Base::identify(Base* p)
{
	if (dynamic_cast<A*>(p))
		std::cout << "A" << std::endl;
	if (dynamic_cast<B*>(p))
		std::cout << "B" << std::endl;
	if (dynamic_cast<C*>(p))
		std::cout << "C" << std::endl;	
}

void Base::identify(Base& p)
{
	try {
		A& a = dynamic_cast<A&>(p);
		(void)a;
		std::cout << "A" << std::endl;
		return;
	} catch (...) {}

	try {
		B& b = dynamic_cast<B&>(p);
		(void)b;
		std::cout << "B" << std::endl;
		return;
	} catch (...) {}

	try {
		C& c = dynamic_cast<C&>(p);
		(void)c;
		std::cout << "C" << std::endl;
		return;
	} catch (...) {
		std::cout << "Unknown type" << std::endl;
	}

}
