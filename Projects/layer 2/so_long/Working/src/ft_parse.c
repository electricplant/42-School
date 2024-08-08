/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:41:45 by dgerhard          #+#    #+#             */
/*   Updated: 2024/24/07 17:04:41 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reqs.h"

int	ft_parse(t_data *img) //open file, fill matrix with map
{
	int	err;

	err = 0;
	img->file.fd = open(img->file.filename, O_RDONLY);
	if (img->file.fd == -1)
		ft_error("File descriptor failed", img);
	img->file.line = get_next_line(img->file.fd);
	img->map_x = ft_strlen(img->file.line) - 1;
	while (img->file.line)
	{
		img->map_y++;
		if (img->map_x != (ft_strlen(img->file.line) - 1))
			err = 1;
		free(img->file.line);
		img->file.line = get_next_line(img->file.fd);
	}
	close(img->file.fd);
	if (img->map_x == img->map_y || err == 1)
		ft_error("Bad Dimensions!", img);
	img->win_x = img->map_x * img->txtr.textr_size;
	img->win_y = img->map_y * img->txtr.textr_size;
	return (0);
}

int	init_matrix(t_data *img)
{
	int		i;

	i = 0;
	img->matrix = (char **)malloc(img->map_y * sizeof(char *));
	if (img->matrix == NULL)
		ft_error("matrix error", img);
	while (i < img->map_y)
	{
		img->matrix[i] = (char *)malloc((img->map_x) * sizeof(char));
		if (img->matrix[i] == NULL)
			ft_error("matrix allocation error", img);
		i++;
	}
	ft_fill_map(img);
	return (0);
}

int	ft_fill_map(t_data *img)
{
	int	i;
	int	err;

	i = 0;
	err = 0;
	img->file.fd = open(img->file.filename, O_RDONLY);
	if (img->file.fd == -1)
		ft_error("Printmap bad", img);
	while (i <= (img->map_y - 1))
	{
		img->file.line = get_next_line(img->file.fd);
		if (ft_fill_line(img, i))
			err = 1;
		free(img->file.line);
		img->file.line = NULL;
		i++;
	}
	close(img->file.fd);
	if (img->p_x_axis == 0 || err == 1)
		ft_error("Missing Player Position/Weird char", img);
	ft_check_walls(img);
	if (img->txtr.num_colls < 1 || img->txtr.num_exits != 1)
		ft_error("Bad num of Collectibles/Exits!", img);
	return (0);
}

int	ft_fill_line(t_data *img, int i)
{
	int		j;
	char	step;

	j = 0;
	step = '0';
	while (j < img->map_x)
	{
		step = img->file.line[j];
		if (step == 'C')
			img->txtr.num_colls++;
		else if (step == 'E')
			img->txtr.num_exits++;
		else if (step == 'P')
		{
			img->p_x_axis = j;
			img->p_y_axis = i;
		}
		else if (step != '1' && step != '0')
			return (1);
		img->matrix[i][j] = step;
		j++;
	}
	return (0);
}
