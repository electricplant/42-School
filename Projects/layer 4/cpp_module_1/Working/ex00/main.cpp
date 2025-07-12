/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:50:08 by dgerhard          #+#    #+#             */
/*   Updated: 2025/07/11 12:51:37 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int	main(void)
{
	Zombie* zombie = NULL;

	zombie = zombie->newZombie("Taco");
	zombie->randomChump("Greeb");

	delete(zombie);

}