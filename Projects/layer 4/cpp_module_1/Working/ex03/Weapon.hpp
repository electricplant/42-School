/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:40:02 by dgerhard          #+#    #+#             */
/*   Updated: 2025/07/13 11:23:18 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
# define WEAPON_HPP

# include <string.h>
# include <iostream>

class Weapon
{
	std::string	type;
	public:
		Weapon(std::string type);
		const std::string& getType();
		void setType(std::string newtype);
};

#endif