/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 08:46:10 by dgerhard          #+#    #+#             */
/*   Updated: 2025/07/21 09:37:34 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

class AMateria
{
	protected:
		std::string _type;

	public:
		AMateria();
		~AMateria();
		AMateria(std::string const& type);

		AMateria(const AMateria& src);
		AMateria& operator=(AMateria const &other);
		std::string const &getType() const;
		
		virtual AMateria* clone () const = 0;
		virtual void use(ICharacter& target);
};