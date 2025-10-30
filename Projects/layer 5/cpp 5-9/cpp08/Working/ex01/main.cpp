/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 08:36:38 by dgerhard          #+#    #+#             */
/*   Updated: 2025/10/30 09:58:54 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

int main()
{
	try
	{
		Span test(5);

		std::cout << "Adding 1 number" << std::endl;
		
		test.addNumber(1);

		std::cout << "Attempting test.shortestSpan()" << std::endl;

		test.shortestSpan();
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	std::cout << std::endl;

	try
	{
		Span test(5);

		std::cout << "Adding 5 numbers" << std::endl;
		
		test.addNumber(1);
		test.addNumber(2);
		test.addNumber(5);
		test.addNumber(6);
		test.addNumber(9);

		std::cout << "Adding 1 extra number" << std::endl;

		test.addNumber(69);
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	std::cout << std::endl << "Subject test: " << std::endl;

	{
		Span sp = Span(5);
		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);
		std::cout << sp.shortestSpan() << std::endl;
		std::cout << sp.longestSpan() << std::endl;
	}

	std::cout << std::endl << "Multiple input test: " << std::endl;
	
	try
	{
		Span sp = Span(5);
		int arr[] = {1, 2, 3, 4, 5};
		std::vector<int> numbers(arr, arr + sizeof(arr)/sizeof(arr[0]));
		std::cout << "Adding range of numbers" << std::endl;
		sp.addNumbers(numbers.begin(), numbers.end());
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}





	return 0;
}