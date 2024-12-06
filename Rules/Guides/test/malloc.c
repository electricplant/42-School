#include "header.h"

void init_mem_tracker(t_mem_tracker *tracker)
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

void *ft_malloc(t_mem_tracker *tracker ,size_t size)
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

void add_address(t_mem_tracker *tracker, void *address)
{
	tracker->capacity += 1;
	tracker->addresses = realloc(tracker->addresses, sizeof(void *) * tracker->capacity);
	if (!tracker->addresses)
	{
		perror("realloc");
		exit(EXIT_FAILURE);
	}
	tracker->addresses[tracker->capacity - 1] = address;
}

void free_all(t_mem_tracker *tracker)
{
	size_t	i;

	i = 0;
	while (i < tracker->capacity)
	{
		printf("Freeing address %p\n", tracker->addresses[i]);
		free(tracker->addresses[i]);
		i++;
	}
	free(tracker->addresses);
	tracker->addresses = NULL;
	tracker->capacity = 0;
}

// int	main(void)
// {
// 	t_mem_tracker	tracker;

// 	init_memory_tracker(&tracker);
// 	ft_malloc(&tracker, 10);
// 	//ft_malloc(tracker, 20);
// 	//ft_malloc(tracker, 30);
// 	free_all(&tracker);
// 	return (0);
// }