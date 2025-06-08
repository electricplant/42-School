/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:06:47 by dgerhard          #+#    #+#             */
/*   Updated: 2025/06/08 10:29:10 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"
#include <iostream>

int main(void)
{
	DiamondTrap Pikachu("Pikachu");
	DiamondTrap Charmander("Charmander");
	DiamondTrap Ditto("Ditto");

	Pikachu.whoAmI();
	Charmander.whoAmI();
	Ditto.whoAmI();
	Pikachu.attack("Charmander");
	Charmander.takeDamage(5);
	Ditto.beRepaired(3);
}