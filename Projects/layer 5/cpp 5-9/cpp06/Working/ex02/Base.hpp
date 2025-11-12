/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 09:57:50 by dgerhard          #+#    #+#             */
/*   Updated: 2025/11/12 06:52:23 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class Base
{
	public:
		virtual ~Base();
		static Base * generate(void);
		static void identify(Base* p);
		static void identify(Base& p);
};

class A : public Base{};
class B : public Base{};
class C : public Base{};
