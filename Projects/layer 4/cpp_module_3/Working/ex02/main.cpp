/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:06:47 by dgerhard          #+#    #+#             */
/*   Updated: 2025/06/08 09:48:30 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"
#include <iostream>

int main(void)
{
	ClapTrap dude("duder");
	ScavTrap bees("bees");
	FragTrap jojo("jojo");

	dude.attack("sherry");
	bees.attack("agke");
	jojo.attack("mike");
	jojo.highFivesGuys();
	bees.beRepaired(20);
}