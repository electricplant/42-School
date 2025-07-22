/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:35:21 by dgerhard          #+#    #+#             */
/*   Updated: 2025/07/22 12:21:28 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"

void IMateriaSource::learnMateria(AMateria* )
{
	
}

IMateriaSource::~IMateriaSource()
{
	std::cout << "Destructor called for IMateriaSource" << std::endl;
}