/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:41:45 by dgerhard          #+#    #+#             */
/*   Updated: 2024/24/07 17:04:41 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "reqs.h"

void	ft_draw_scene(t_data *img)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < img->map_y)
	{
		while (j < img->map_x)
		{
			ft_put_texture(img, img->matrix[i][j], i, j);
			j++;
		}
		j = 0;
		i++;
	}
}

void	ft_move_player(t_data *img, int x, int y)
{
	img->file.prev_x = img->p_x_axis * 64;
	img->file.prev_y = img->p_y_axis * 64;
	x += img->p_x_axis;
	y += img->p_y_axis;
	if (img->matrix[y][x] != '1' && ft_check_exit(img, img->matrix[y][x]))
	{
		mlx_put_image_to_window(img->mlx, img->win, img->txtr.textr[3],
			img->file.prev_x, img->file.prev_y);
		x = x * 64;
		y = y * 64;
		mlx_put_image_to_window(img->mlx, img->win, img->txtr.textr[0], x, y);
		img->p_x_axis = x / 64;
		img->p_y_axis = y / 64;
		update_movements(img);
	}
}

void	ft_put_texture(t_data *img, char dingus, int x, int y)
{
	x = x * 64;
	y = y * 64;
	if (dingus == '1')
		mlx_put_image_to_window(img->mlx, img->win, img->txtr.textr[1], y, x);
	else if (dingus == '0' || dingus == 'P')
		mlx_put_image_to_window(img->mlx, img->win, img->txtr.textr[3], y, x);
	else if (dingus == 'C')
		mlx_put_image_to_window(img->mlx, img->win, img->txtr.textr[4], y, x);
	else if (dingus == 'E')
		mlx_put_image_to_window(img->mlx, img->win, img->txtr.textr[2], y, x);
}

int	ft_texture_paths(t_data *img)
{
	img->txtr.textr[0] = mlx_xpm_file_to_image(img->mlx,
			PLAYER_PATH, &img->width, &img->height);
	img->txtr.textr[1] = mlx_xpm_file_to_image(img->mlx,
			WALL_PATH, &img->width, &img->height);
	img->txtr.textr[2] = mlx_xpm_file_to_image(img->mlx,
			EXIT_PATH, &img->width, &img->height);
	img->txtr.textr[3] = mlx_xpm_file_to_image(img->mlx,
			FLOOR_PATH, &img->width, &img->height);
	img->txtr.textr[4] = mlx_xpm_file_to_image(img->mlx,
			COLL_PATH, &img->width, &img->height);
	return (0);
}

void	update_movements(t_data *img)
{
	ft_putstr_fd("\nSteps:", 1);
	ft_putnbr_fd(img->num_movs, 1);
	img->num_movs++;
}
