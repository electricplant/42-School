/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 16:12:07 by dgerhard          #+#    #+#             */
/*   Updated: 2025/11/12 07:19:43 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdexcept>

template <typename T>
class Array
{
	private:
		T* _array;
		unsigned int _size;

	public:
		Array() : _array(NULL), _size(0) {}

		Array(unsigned int n) : _array(new T[n]()), _size(n) {}

		Array(const Array& other) : _array(new T[other._size]), _size(other._size)
		{
			for (unsigned int i = 0; i < _size; i++)
			{
				_array[i] = other._array[i];
			}
		}

		Array& operator=(const Array& other)
		{
			if (this != &other)
			{
				delete[] _array;
				_size = other._size;
				_array = new T[_size];
				for (unsigned int i = 0; i < _size; i++)
				{
					_array[i] = other._array[i];
				}
			}
			return *this;
		}

		T& operator[](unsigned int index)
		{
			if (index >= _size)
				throw std::out_of_range("Index out of bounds");
			return _array[index];
		}

		const T& operator[](unsigned int index) const
		{
			if (index >= _size)
				throw std::out_of_range("Index out of bounds");
			return _array[index];
		}

		unsigned int size() const
		{
			return _size;
		}
		

		~Array()
		{
			delete[] _array;
		}
};
