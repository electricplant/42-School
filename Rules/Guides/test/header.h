#ifndef HEADER_H
# define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_mem_tracker
{
	void **addresses;
	size_t capacity;
}					t_mem_tracker;

typedef struct s_data
{
	t_mem_tracker	tracker;
}				t_data;

void	init_mem_tracker(t_mem_tracker *tracker);
void	*ft_malloc(t_mem_tracker *tracker ,size_t size);
void	add_address(t_mem_tracker *tracker, void *address);
void	free_all(t_mem_tracker *tracker);

# endif