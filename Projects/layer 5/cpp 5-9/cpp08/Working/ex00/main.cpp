/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 08:52:28 by dgerhard          #+#    #+#             */
/*   Updated: 2025/10/29 09:35:02 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <set>
#include <vector>
#include <iostream>
#include "easyfind.hpp"

int main() {
	std::set<int> numbers;
	numbers.insert(1);
	numbers.insert(2);
	numbers.insert(3);

	try {
		std::set<int>::iterator it = easyfind(numbers, 2);
		std::cout << "Found: " << *it << std::endl;
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	return 0;
}