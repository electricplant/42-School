/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:28:10 by dgerhard          #+#    #+#             */
/*   Updated: 2024/12/13 15:09:24 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_mem_tracker(t_mem_tracker *tracker)
{
	tracker->addresses = malloc(sizeof(void *) * 1);
	if (!tracker->addresses)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	tracker->addresses[0] = NULL;
	tracker->capacity = 1;
}

void	*ft_malloc(t_mem_tracker *tracker, size_t size)
{
	void	*ptr;

	printf("Allocating %zu bytes\n", size);
	ptr = malloc(size);
	if (!ptr)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	add_address(tracker, ptr);
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

void	free_trkr(t_mem_tracker *tracker)
{
	size_t	i;

	i = 0;
	while (i < tracker->capacity)
	{
		if (tracker->addresses[i] != NULL)
		{
			printf("Freeing address %p\n", tracker->addresses[i]);
			free(tracker->addresses[i]);
		}
		i++;
	}
	free(tracker->addresses);
	tracker->addresses = NULL;
	tracker->capacity = 0;
}
