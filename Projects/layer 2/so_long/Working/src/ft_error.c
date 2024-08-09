/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:41:45 by dgerhard          #+#    #+#             */
/*   Updated: 2024/24/07 17:04:41 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reqs.h"

int	ft_error(char *str, t_data *img)
{
	write(2, "\nError\n", 7);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	if (img->matrix != NULL)
		free_matrix(img);
	if (img->mlx != NULL)
		ft_free_mlx(img);
	exit(1);
}

void	ft_free_mlx(t_data *img)
{
	mlx_destroy_image(img->mlx, img->txtr.textr[0]);
	mlx_destroy_image(img->mlx, img->txtr.textr[1]);
	mlx_destroy_image(img->mlx, img->txtr.textr[2]);
	mlx_destroy_image(img->mlx, img->txtr.textr[3]);
	mlx_destroy_image(img->mlx, img->txtr.textr[4]);
	mlx_destroy_window(img->mlx, img->win);
	mlx_destroy_display(img->mlx);
	free(img->mlx);
	return ;
}

int	free_matrix(t_data *img)
{
	int	i;

	i = 0;
	if (img->matrix == NULL)
		return (0);
	i = img->map_y;
	while (i > 0)
	{
		if (img->matrix[i - 1])
			free(img->matrix[i - 1]);
		i--;
	}
	free(img->matrix);
	return (0);
}
