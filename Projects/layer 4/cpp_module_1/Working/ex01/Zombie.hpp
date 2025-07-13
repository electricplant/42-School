/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:10:30 by dgerhard          #+#    #+#             */
/*   Updated: 2025/07/13 09:42:47 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <string>
# include <iostream>

class Zombie
{
	public:
		Zombie();
		~Zombie();
		Zombie*	newZombie(std::string name);
		void	setName(std::string name);
		void	announce();
	private:
		std::string	name;
	};

	Zombie* zombieHorde( int N, std::string name );

#endif