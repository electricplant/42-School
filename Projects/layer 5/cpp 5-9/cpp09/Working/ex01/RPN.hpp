/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 08:05:19 by dgerhard          #+#    #+#             */
/*   Updated: 2025/11/07 10:40:23 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdexcept>
#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <climits>
//take input
//add each item to a stack
//process stack, adding result to a big variable

class RPN
{
	private:
		long long int _result;
		std::stack<int> _stack;
		RPN();
		void processInput(const std::string& input);
		
	public:
		int getResult() const;
		explicit RPN(const std::string& input);
		RPN(const RPN& other);
		RPN& operator=(const RPN& other);
		~RPN();
};


std::ostream& operator<<(std::ostream& os, const RPN& Rpn);

