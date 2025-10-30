/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 08:36:57 by dgerhard          #+#    #+#             */
/*   Updated: 2025/10/30 09:54:42 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <vector>
#include <iostream>
#include <climits>

class Span
{
	private:
		unsigned int _maxSize;
		std::vector<int> _numbers;
		Span();

	public:
		Span(unsigned int N);
		Span(Span const &other);
		Span &operator=(Span const &other);
		~Span();

		void addNumber(const int recruit);
		int shortestSpan();
		int longestSpan();

		template<typename Iterator>
		void addNumbers(Iterator begin, Iterator end)
		{
			unsigned int distance = std::distance(begin, end);
			if (_numbers.size() + distance > _maxSize)
				throw std::runtime_error("Not enough space in Span");
			_numbers.insert(_numbers.end(), begin, end);
		}
};