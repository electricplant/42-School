/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:28:19 by dgerhard          #+#    #+#             */
/*   Updated: 2024/12/13 15:09:24 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//run "cc main.c malloc.c external_use.c"
//then "valgrind ./a.out"

#include "header.h"

int	main(void)
{
	char			*str;
	t_data			data;

	init_mem_tracker(&data.trkr); //inside data struct = nested

	ft_malloc(&data.trkr, 10); //three random tests
	ft_malloc(&data.trkr, 20);
	ft_malloc(&data.trkr, 30);

	ft_example(&data); //example of external use

	str = strdup("Hello, world!"); //when a function that mallocs is used, we do this:
	add_address(&data.trkr, str);

	free_trkr(&data.trkr);

	str = strdup("Hello, world2!");
	add_address(&data.trkr, str);
	ft_malloc(&data.trkr, 40);

	free_trkr(&data.trkr);
	return (0);
}
