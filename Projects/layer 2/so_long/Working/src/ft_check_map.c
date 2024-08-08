/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:41:45 by dgerhard          #+#    #+#             */
/*   Updated: 2024/24/07 17:04:41 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "reqs.h"

t_data	make_deep_copy(t_data src)
{
	t_data	copy;
	int		i;

	i = 0;
	copy.map_x = src.map_x;
	copy.map_y = src.map_y;
	copy.txtr.num_colls = src.txtr.num_colls;
	copy.txtr.num_exits = src.txtr.num_exits;
	copy.matrix = (char **) malloc (sizeof(char *) * src.map_y);
	if (!copy.matrix)
		ft_error("Matrix copy Column failed", &src);
	while (i < src.map_y)
	{
		copy.matrix[i] = (char *) malloc (sizeof(char) * src.map_x);
		if (!copy.matrix[i])
			ft_error("Matrix copy Row failed", &src);
		ft_memcpy(copy.matrix[i], src.matrix[i], src.map_x);
		i++;
	}
	return (copy);
}

void	ft_verify_map(t_data *img2, int x, int y)
{
	char	step;

	step = img2->matrix[y][x];
	img2->matrix[y][x] = '1';
	if (step == 'C')
		img2->txtr.num_colls--;
	if (step == 'E')
		img2->txtr.num_exits--;
	if (img2->matrix[y][x - 1] != '1')
		ft_verify_map(img2, x - 1, y);
	if (img2->matrix[y][x + 1] != '1')
		ft_verify_map(img2, x + 1, y);
	if (img2->matrix[y - 1][x] != '1')
		ft_verify_map(img2, x, y - 1);
	if (img2->matrix[y + 1][x] != '1')
		ft_verify_map(img2, x, y + 1);
	if ((img2->txtr.num_colls != 0) && (img2->txtr.num_exits != 0))
		ft_error("Bad num of Colls/Exits", img2);
}

void	ft_check_walls(t_data *img)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j <= (img->map_x - 1))
	{
		if (img->matrix[0][j] != '1')
			ft_error("Missing Top Row Wall!", img);
		if (img->matrix[img->map_y - 1][j] != '1')
			ft_error("Missing Bottom Row Wall!", img);
		j++;
	}
	while (i <= (img->map_y - 1))
	{
		if ((img->matrix[i][0] != '1') ||
				(img->matrix[i][img->map_x - 1] != '1'))
			ft_error("Missing Column Wall!", img);
		i++;
	}
	return ;
}

void	ft_check_textures(t_data *img)
{
	int	fd;

	fd = open(PLAYER_PATH, O_RDONLY);
	if (fd == -1)
		ft_error("Missing Player texture", img);
	close(fd);
	fd = open(WALL_PATH, O_RDONLY);
	if (fd == -1)
		ft_error("Missing Wall texture", img);
	close(fd);
	fd = open(EXIT_PATH, O_RDONLY);
	if (fd == -1)
		ft_error("Missing Exit texture", img);
	close(fd);
	fd = open(FLOOR_PATH, O_RDONLY);
	if (fd == -1)
		ft_error("Missing Floor texture", img);
	close(fd);
	fd = open(COLL_PATH, O_RDONLY);
	if (fd == -1)
		ft_error("Missing Collectible texture", img);
	close(fd);
	return ;
}
