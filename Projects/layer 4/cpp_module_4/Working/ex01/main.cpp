/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 15:02:32 by dgerhard          #+#    #+#             */
/*   Updated: 2025/07/21 08:44:46 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int	main()
{
	const Animal *array[100];
	int i = 0;

	while(i < 50)
		array[i++] = new Cat();
	while(i < 100)
		array[i++] = new Dog();

	array[10]->makeSound();
	array[51]->makeSound();
	array[1]->makeSound();
	array[99]->makeSound();

	for (i = 0; i < 100; i++)
		delete array[i];
	
	return 0;
}