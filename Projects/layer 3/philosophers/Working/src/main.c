/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 11:23:11 by dgerhard          #+#    #+#             */
/*   Updated: 2024/10/13 13:31:11 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	main(int argc, char **argv)
{
	if (argc == 4)
	{
		ft_printf("hello");
	}
	else if (argc == 5)
	{
		ft_printf("hello");
	}
	else
		ft_printf("hi");
	(void)argv;
	return (0);
}