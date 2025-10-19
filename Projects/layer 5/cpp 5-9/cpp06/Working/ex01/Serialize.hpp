/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serialize.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 09:32:16 by dgerhard          #+#    #+#             */
/*   Updated: 2025/10/19 14:48:33 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Data.hpp"

#include <iostream>
#include <stdint.h>

class Serialize
{
	private:
		Serialize(void);
		Serialize(const Serialize& other);
		Serialize& operator=(const Serialize& other);
		~Serialize(void);

	public:
		static uintptr_t serialize(Data* ptr);
		static Data* deserialize(uintptr_t raw);
};