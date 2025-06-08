/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:49:03 by dgerhard          #+#    #+#             */
/*   Updated: 2025/06/08 08:47:39 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

#ifndef FragTrap_HPP
#define FragTrap_HPP

class FragTrap : public ClapTrap
{
	public:
	FragTrap(std::string name);
	~FragTrap();

	void highFivesGuys(void);
	void attack(const std::string& target);
};

#endif