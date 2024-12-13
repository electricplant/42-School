/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:28:10 by dgerhard          #+#    #+#             */
/*   Updated: 2024/12/13 13:01:09 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_mem_tracker(t_mem_tracker *trkr)
{
	trkr->addresses = malloc(sizeof(void *) * 1);
	if (!trkr->addresses)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	trkr->addresses[0] = NULL;
	trkr->capacity = 1;
}

void	*ft_malloc(t_mem_tracker *trkr, size_t size)
{
	void	*ptr;

	printf("Allocating %zu bytes\n", size);
	ptr = malloc(size);
	if (!ptr)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	add_address(trkr, ptr);
	return (ptr);
}

void	add_address(t_mem_tracker *trkr, void *address)
{
	trkr->capacity += 1;
	trkr->addresses = realloc(trkr->addresses, sizeof(void *) * trkr->capacity);
	if (!trkr->addresses)
	{
		perror("realloc");
		exit(EXIT_FAILURE);
	}
	trkr->addresses[trkr->capacity - 1] = address;
}

void	free_all(t_mem_tracker *trkr)
{
	size_t	i;

	i = 0;
	while (i < trkr->capacity)
	{
		if (trkr->addresses[i] != NULL)
		{
			printf("Freeing address %p\n", trkr->addresses[i]);
			free(trkr->addresses[i]);
		}
		i++;
	}
	free(trkr->addresses);
	trkr->addresses = NULL;
	trkr->capacity = 0;
}
