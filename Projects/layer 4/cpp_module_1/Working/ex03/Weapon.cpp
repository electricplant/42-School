/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:45:29 by dgerhard          #+#    #+#             */
/*   Updated: 2025/07/13 11:23:28 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon(std::string type)
{
	setType(type);
}

const std::string& Weapon::getType(void)
{
	return (type);
}

void Weapon::setType(std::string newtype)
{
	type = newtype;
}