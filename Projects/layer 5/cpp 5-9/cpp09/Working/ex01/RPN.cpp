/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 08:05:04 by dgerhard          #+#    #+#             */
/*   Updated: 2025/11/07 10:53:31 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() { };

RPN::RPN(const std::string& input) : _result(1)
{
	try
	{
		processInput(input);
		_result = _stack.top();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		_result = 0;
	}
	
}
RPN::RPN(const RPN& other)
{
	*this = other;
}
RPN& RPN::operator=(const RPN& other)
{
	if (this != &other)
	{
		_result = other._result;
		_stack = other._stack;
	}
	return *this;
}
RPN::~RPN()
{
	
}

int RPN::getResult() const
{
	return (_result);
}

void doOperation(const char c, std::stack<int>& _stack)
{
	int a;
	int b;
	long long result;

	b = _stack.top();
	_stack.pop();
	a = _stack.top();
	_stack.pop();

	// std::cout << "Doing: " << a;

	switch (c)
	{
		case '*':
			result = static_cast<long long>(a) * b;
			if (result > INT_MAX || result < INT_MIN)
				throw std::runtime_error("Error: integer overflow");
			_stack.push(static_cast<int>(result));
			break;
		case '+':
			result = static_cast<long long>(a) + b;
			if (result > INT_MAX || result < INT_MIN)
				throw std::runtime_error("Error: integer overflow");
			_stack.push(static_cast<int>(result));
			break;
		case '-':
			result = static_cast<long long>(a) - b;
			if (result > INT_MAX || result < INT_MIN)
				throw std::runtime_error("Error: integer overflow");
			_stack.push(static_cast<int>(result));
			break;
		case '/':
			if (b == 0)
				throw std::runtime_error("Error: division by zero");
			_stack.push(a / b);
			break;
	}
	// std::cout << b << "\n";
}

void RPN::processInput(const std::string& input)
{
	std::istringstream iss(input);
	std::string token;
	char c = '0';
	int num = 0;

	// std::cout << "Processing: " << input << "\n";
	while(iss >> token)
	{
		if (token.length() != 1)
			throw std::runtime_error("Error: invalid token length");
		c = token[0];
		if (c >= '0' && c <= '9')
		{
			// std::cout << "Adding: " << c << "\n";
			num = c - '0';
			_stack.push(num);
		}
		else if (c == '*' || c == '+' || c == '-' || c == '/')
		{
			if (_stack.size() < 2)
				throw std::runtime_error("Error: need at least 2 number inputs before operator");
			doOperation(c, _stack);
		}
		else
			throw std::runtime_error("Error: invalid character");
	}
}

std::ostream& operator<<(std::ostream& os, const RPN& Rpn)
{
	os << Rpn.getResult();
	return os;
}