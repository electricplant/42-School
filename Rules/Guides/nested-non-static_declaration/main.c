/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:28:19 by dgerhard          #+#    #+#             */
/*   Updated: 2024/12/09 11:47:38 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//run "cc main.c malloc.c external_use.c"
//then "valgrind ./a.out"

#include "header.h"

int	main(void)
{
	char			*str;
	t_data			data;

	init_mem_tracker(&data.tracker); //inside data struct = nested

	ft_malloc(&data.tracker, 10); //three random tests
	ft_malloc(&data.tracker, 20);
	ft_malloc(&data.tracker, 30);

	ft_example(&data); //example of external use

	str = strdup("Hello, world!"); //when a function that mallocs is used, we do this:
	add_address(&data.tracker, str);

	free_all(&data.tracker);
	return (0);
}
