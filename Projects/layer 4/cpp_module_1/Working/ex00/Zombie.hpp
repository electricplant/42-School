/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:10:30 by dgerhard          #+#    #+#             */
/*   Updated: 2025/05/03 10:51:30 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <string>
# include <iostream>

class Zombie
{
	std::string	name;
	public:
		Zombie() {}
		void setName(std::string zombieName);
		void announce(void);
};

Zombie*	newZombie(std::string name);
void	randomChump(std::string name);

#endif