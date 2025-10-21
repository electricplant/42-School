/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whateva.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 09:29:44 by dgerhard          #+#    #+#             */
/*   Updated: 2025/10/21 09:48:12 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

template <typename Toop>
void swap(Toop &one, Toop &two)
{
	Toop temp = one;
	one = two;
	two = temp;
}

template <typename Toop>
Toop max(const Toop &one, const Toop &two)
{
	if (one <= two)
		return two;
	else
		return one;
}

template <typename Toop>
Toop min(const Toop &one,const Toop &two)
{
	if (two <= one)
		return two;
	else
		return one;
}