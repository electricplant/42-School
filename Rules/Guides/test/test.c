#include "header.h"

int	main(void)
{
	char *str;
	t_mem_tracker	tracker;
	t_data			data;

	init_mem_tracker(&tracker);
	init_mem_tracker(&data.tracker);

	ft_malloc(&tracker, 10);
	ft_malloc(&tracker, 20);
	ft_malloc(&tracker, 30);

	ft_malloc(&data.tracker, 10);
	ft_malloc(&data.tracker, 20);
	ft_malloc(&data.tracker, 30);

	str = strdup("Hello, world!");
	add_address(&tracker, str);
	free_all(&tracker);
	free_all(&data.tracker);
	return (0);
}