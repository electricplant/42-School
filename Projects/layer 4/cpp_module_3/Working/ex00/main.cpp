/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:06:47 by dgerhard          #+#    #+#             */
/*   Updated: 2025/06/06 13:43:57 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include <iostream>

int main(void)
{
	ClapTrap dude("duder");
	ClapTrap bob("bob");

	dude.attack("sheldon");
	bob.takeDamage(3);
	bob.takeDamage(3);
	bob.takeDamage(3);
	bob.takeDamage(3);
	bob.takeDamage(3);
	bob.attack("genri");
	bob.beRepaired(10);
}