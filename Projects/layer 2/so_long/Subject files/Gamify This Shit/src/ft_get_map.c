/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:34:38 by dgerhard          #+#    #+#             */
/*   Updated: 2024/05/17 16:34:41 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reqs.h"

int	ft_get_map(char *file, t_map *map) //something going wrong with the struct being sent
{
	int		fd;
	char	*line;
	int		i;

	line = NULL;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	i = 0;
	while (get_next_line(fd) > 0)
		map->rows++;
	close(fd);
	fd = open(file, O_RDONLY);
	map->map = malloc(sizeof(char *) * map->rows);
	if (map->map == NULL)
		return (0);
	while (get_next_line(fd) > 0)
	{
		line = get_next_line(fd);
		map->map[i] = ft_strdup(line);
		free(line);
		i++;
	}
	close(fd);
	return (1);
}