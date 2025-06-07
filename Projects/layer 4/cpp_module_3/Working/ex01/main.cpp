/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:06:47 by dgerhard          #+#    #+#             */
/*   Updated: 2025/06/07 14:16:50 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include <iostream>

int main(void)
{
	ClapTrap dude("duder");
	ScavTrap bees("bees");

	dude.attack("sherry");
	bees.attack("agke");
	bees.beRepaired(20);
}