/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomChump.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:53:43 by dgerhard          #+#    #+#             */
/*   Updated: 2025/04/19 20:28:16 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

void	randomChump(std::string name)
{
	Zombie* zombie = newZombie(name);

	zombie->announce();

	std::cout << "Destroyed : " << name << std::endl;
	delete zombie;
}