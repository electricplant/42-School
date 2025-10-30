/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 08:54:24 by dgerhard          #+#    #+#             */
/*   Updated: 2025/10/30 09:48:18 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

Span::Span() : _maxSize(0) { }

Span::Span(unsigned int N) : _maxSize(N)
{
	_numbers.reserve(_maxSize);
}

Span::Span(Span const &other) : _maxSize(other._maxSize)
{
	*this = other;
}
Span &Span::operator=(Span const &other)
{
	if (this != &other)
	{
		_maxSize = other._maxSize;
	}
	return *this;
}
Span::~Span()
{
	std::cout << "default destructor called" << std::endl;
}

void Span::addNumber(const int recruit)
{
	if (_numbers.size() >= _maxSize)
		throw std::runtime_error("Span is full");
	_numbers.push_back(recruit);
}

int Span::shortestSpan()
{
	if (_numbers.size() < 2)
		throw std::runtime_error("Not enough members to find span");

	std::vector<int> sorted(_numbers);
	std::sort(sorted.begin(), sorted.end());
	int minSpan = INT_MAX;
	for (size_t i = 1; i < sorted.size(); ++i)
	{
		int span = sorted[i] - sorted[i - 1];
		minSpan = std::min(minSpan, span);
	}
	return minSpan;
}

int Span::longestSpan()
{
	if (_numbers.size() < 2)
		throw std::runtime_error("Not enough members to find span");

	std::vector<int>::iterator min = std::min_element(_numbers.begin(), _numbers.end());
	std::vector<int>::iterator max = std::max_element(_numbers.begin(), _numbers.end());

	return *max - *min;
}