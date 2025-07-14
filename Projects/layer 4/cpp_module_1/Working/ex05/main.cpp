/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:16:10 by dgerhard          #+#    #+#             */
/*   Updated: 2025/07/14 13:19:48 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int	main(int argc, char *argv[])
{
	Harl Harl2;

	if (argc == 2)
	{
		Harl2.complain(argv[1]);
	}
	// Harl2.complain("INFO");

}