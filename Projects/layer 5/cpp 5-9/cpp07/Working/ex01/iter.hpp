/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:25:33 by dgerhard          #+#    #+#             */
/*   Updated: 2025/10/24 13:38:23 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iter.hpp"
#include <cstddef>

template <typename Toop, typename Func>
void iter(Toop* array, size_t length, Func f)
{
	for (size_t i = 0; i < length; i++)
	{
		f(array[i]);
	}
}