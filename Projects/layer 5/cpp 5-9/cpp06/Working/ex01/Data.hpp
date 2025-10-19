/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 09:45:30 by dgerhard          #+#    #+#             */
/*   Updated: 2025/10/19 14:37:59 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

#include <iostream>

class Data
{
	private:
		int _size;

	public:
		Data();
		Data(Data const &other);
		Data &operator=(Data const &other);
		~Data();
		
		int getSize() const;
};

std::ostream &operator<<(std::ostream &o, Data const &other);