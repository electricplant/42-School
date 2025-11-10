/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 07:44:29 by dgerhard          #+#    #+#             */
/*   Updated: 2025/11/10 09:28:07 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other) : _vect(other._vect), _deque(other._deque) {}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		_vect = other._vect;
		_deque = other._deque;
	}
	return *this;
}

PmergeMe::~PmergeMe() {}

bool PmergeMe::isValidNum(const char *str)
{
	if (!str || str[0] == '\0')
		return false;

	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return false;
	}

	char *ptr;
	long num = strtol(str, &ptr, 10);

	if (*ptr != '\0' || num < 0 || num > INT_MAX)
		return false;

	return true;
	}

bool PmergeMe::parseArgs(int argc, char **argv)
	{
	if (argc < 2)
		return false;

	for (int i = 1; i < argc; i++)
	{
		if (!isValidNum(argv[i]))
			return (false);

		int num = atoi(argv[i]);
		_vect.push_back(num);
		_deque.push_back(num);
	}

	return true;
}

std::vector<int> PmergeMe::getJacobSeq(size_t size)
	{
	std::vector<int> jacobsthal;
	jacobsthal.push_back(0);
	jacobsthal.push_back(1);

	jacobsthal.reserve(size);

	while (jacobsthal.back() < static_cast<int>(size))
	{
		int lastNum = jacobsthal.back();
		int secondLastNum = jacobsthal[jacobsthal.size() - 2];
		
		int next = lastNum + 2 * secondLastNum;
		jacobsthal.push_back(next);
	}

	return jacobsthal;
}

std::vector<int> PmergeMe::getInsertPos(size_t size)
{
	std::vector<int> jacobSeq = getJacobSeq(size);
	std::vector<int> order;
	std::vector<bool> used(size, false);
	used[0] = true;

	for (size_t i = 1; i < jacobSeq.size() && jacobSeq[i] < static_cast<int>(size); i++)
	{
		if (!used[jacobSeq[i]]) {
			order.push_back(jacobSeq[i]);
			used[jacobSeq[i]] = true;
		}
		
		for (int j = jacobSeq[i] - 1; j > jacobSeq[i-1]; j--) {
			if (j < (int)size && !used[j]) {
				order.push_back(j);
				used[j] = true;
			}
		}
	}

	for (size_t i = 1; i < size; i++) {
		if (!used[i]) {
			order.push_back(i);
		}
	}

	return order;
	}

	void PmergeMe::sortVector()
	{
	if (_vect.size() <= 1)
		return;

	bool hasStraggler = false;
	int straggler = 0;

	if (_vect.size() % 2 != 0)
	{
		hasStraggler = true;
		straggler = _vect.back();
		_vect.pop_back();
	}

	std::vector<std::pair<int, int> > pairs;
	for (size_t i = 0; i < _vect.size(); i += 2)
	{
		int first = _vect[i];
		int second = _vect[i + 1];
		if (first < second)
			std::swap(first, second);
		pairs.push_back(std::make_pair(first, second));
	}

	std::vector<int> mainChain;
	for (size_t i = 0; i < pairs.size(); i++)
	{
		mainChain.push_back(pairs[i].first);
	}

	if (mainChain.size() > 1)
	{
		_vect = mainChain;
		sortVector();
		mainChain = _vect;
	}

	std::vector<int> result = mainChain;

	std::vector<int> pendChain;
	for (size_t i = 0; i < pairs.size(); i++)
	{
		pendChain.push_back(pairs[i].second);
	}

	if (!pendChain.empty())
	{
		std::vector<int>::iterator pos = std::lower_bound(result.begin(), result.end(), pendChain[0]);
		result.insert(pos, pendChain[0]);
	}

	if (pendChain.size() > 1)
	{
		std::vector<int> insertionOrder = getInsertPos(pendChain.size());

		for (size_t i = 0; i < insertionOrder.size(); i++)
		{
			int idx = insertionOrder[i];
			if (idx > 0 && idx < (int)pendChain.size())
			{
				std::vector<int>::iterator pos = std::lower_bound(result.begin(), result.end(),  pendChain[idx]);
				result.insert(pos,  pendChain[idx]);
			}
		}
	}

	if (hasStraggler)
	{
		std::vector<int>::iterator pos = std::lower_bound(result.begin(), result.end(), straggler);
		result.insert(pos, straggler);
	}

	_vect = result;
}

void PmergeMe::sortDeque()
{
	if (_deque.size() <= 1)
		return;

	bool hasStraggler = false;
	int straggler = 0;

	if (_deque.size() % 2 != 0)
	{
		hasStraggler = true;
		straggler = _deque.back();
		_deque.pop_back();
	}

	std::deque<std::pair<int, int> > pairs;
	for (size_t i = 0; i < _deque.size(); i += 2)
	{
		int first = _deque[i];
		int second = _deque[i + 1];
		if (first < second)
			std::swap(first, second);
		pairs.push_back(std::make_pair(first, second));
	}

	std::deque<int> mainChain;
	for (size_t i = 0; i < pairs.size(); i++)
	{
		mainChain.push_back(pairs[i].first);
	}

	if (mainChain.size() > 1)
	{
		_deque = mainChain;
		sortDeque();
		mainChain = _deque;
	}

	std::deque<int> result = mainChain;

	std::deque<int> pendChain;
	for (size_t i = 0; i < pairs.size(); i++)
	{
		pendChain.push_back(pairs[i].second);
	}

	if (!pendChain.empty())
	{
		std::deque<int>::iterator pos = std::lower_bound(result.begin(), result.end(), pendChain[0]);
		result.insert(pos, pendChain[0]);
	}

	if (pendChain.size() > 1)
	{
		std::vector<int> insertionOrder = getInsertPos(pendChain.size());

		for (size_t i = 0; i < insertionOrder.size(); i++)
		{
			int idx = insertionOrder[i];
			if (idx > 0 && idx < (int)pendChain.size())
			{
				std::deque<int>::iterator pos = std::lower_bound(result.begin(), result.end(), pendChain[idx]);
				result.insert(pos, pendChain[idx]);
			}
		}
	}

	if (hasStraggler)
	{
		std::deque<int>::iterator pos = std::lower_bound(result.begin(), result.end(), straggler);
		result.insert(pos, straggler);
	}

	_deque = result;
}

void PmergeMe::sort()
{
	std::vector<int> original = _vect;

	clock_t vecStart = clock();
	sortVector();
	clock_t vecEnd = clock();
	double vecTime = static_cast<double>(vecEnd - vecStart) / CLOCKS_PER_SEC * 1000000;

	clock_t deqStart = clock();
	sortDeque();
	clock_t deqEnd = clock();
	double deqTime = static_cast<double>(deqEnd - deqStart) / CLOCKS_PER_SEC * 1000000;

	std::cout << "Before: ";
	for (size_t i = 0; (i < original.size() && i < 5); ++i) {
		std::cout << original[i];
		if (i < original.size() - 1) std::cout << " ";
		if (i < original.size() - 1 && i == 4) std::cout << "[...]";
	}
	std::cout << std::endl;

	std::cout << "After:  ";
	for (size_t i = 0; (i < _vect.size() && i < 5); ++i) {
		std::cout << _vect[i];
		if (i < _vect.size() - 1) std::cout << " ";
		if (i < original.size() - 1 && i == 4) std::cout << "[...]";
	}
	std::cout << std::endl;

	std::cout << "Time to process a range of " << _vect.size()
				<< " elements with std::vector : " << std::fixed << std::setprecision(5)
				<< vecTime << " us" << std::endl;

	std::cout << "Time to process a range of " << _deque.size()
				<< " elements with std::deque : " << std::fixed << std::setprecision(5)
				<< deqTime << " us" << std::endl;
}