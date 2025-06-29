/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:47:29 by dgerhard          #+#    #+#             */
/*   Updated: 2025/05/04 09:46:12 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANA_HPP
# define HUMANA_HPP

# include "Weapon.hpp"
# include <string.h>
# include <iostream>

class HumanA
{
	std::string _name;
	Weapon& _weapon;
	public:
		HumanA(const std::string& name, Weapon& weapon);
		void attack();
};

#endif