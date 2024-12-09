/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:45:39 by dgerhard          #+#    #+#             */
/*   Updated: 2024/12/09 11:48:30 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	main(void)
{
	char *str;
	t_mem_tracker	tracker; //not declared static, so we can use it in other files

	init_mem_tracker(&tracker);

	ft_malloc(&tracker, 11);
	ft_malloc(&tracker, 21);
	ft_malloc(&tracker, 31);

	ft_example(&tracker);

	str = strdup("Hello, world!");
	add_address(&tracker, str);
	free_all(&tracker);
	return (0);
}