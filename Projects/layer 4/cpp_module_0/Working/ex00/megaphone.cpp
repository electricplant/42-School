/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:46:34 by dgerhard          #+#    #+#             */
/*   Updated: 2025/04/11 11:15:24 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <cctype>

int main (int argc, char **argv)
{
	std::string result;
	if (argc >= 2)
	{
		for (int i = 1; i < argc; ++i)
		{
			for (int k = 0; argv[i][k] != '\0'; ++k)
				result += std::toupper(argv[i][k]);
			if (i < argc - 1)
				result += " ";
		}
	}
	else
		result = "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
	std::cout << result << std::endl;
	return 0;
}
