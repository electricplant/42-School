/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:16:10 by dgerhard          #+#    #+#             */
/*   Updated: 2025/04/28 11:02:26 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int	main(int argc, char **argv)
{
	Harl Harl2;

	if (argc > 2)
	{
		std::cout << "too many inputs" << std::endl;
		return (1);
	}
	else if (argc <= 1)
	{
		Harl2.complain("NONE");
	}
	else
		Harl2.complain(argv[1]);

	
}