/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 07:44:41 by dgerhard          #+#    #+#             */
/*   Updated: 2025/11/10 09:23:12 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	try
	{
		PmergeMe Risotto;
		if (!Risotto.parseArgs(argc, argv))
		{
			std::cout << "input error\n";
			return 1;
		}
		Risotto.sort();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	

}