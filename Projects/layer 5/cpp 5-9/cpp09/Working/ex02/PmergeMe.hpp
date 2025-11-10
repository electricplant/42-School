/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 07:44:18 by dgerhard          #+#    #+#             */
/*   Updated: 2025/11/10 09:09:16 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <deque>
#include <cstdlib>
#include <climits>
#include <iomanip>

class PmergeMe
{
	private:
		std::vector<int> _vect;
		std::deque<int> _deque;
		std::vector<int> getJacobSeq(size_t size);
		void sortDeque();
		void sortVector();
		std::vector<int> getInsertPos(size_t size);
		bool isValidNum(const char *str);
		
	public:
		PmergeMe();
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		~PmergeMe();
		
		bool parseArgs(int argc, char **argv);
		void sort();
};