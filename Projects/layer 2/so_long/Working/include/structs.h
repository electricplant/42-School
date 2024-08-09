/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:41:45 by dgerhard          #+#    #+#             */
/*   Updated: 2024/24/07 17:04:41 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_file {
	int		fd;
	int		line_length;
	char	*line;
	char	*filename;
	int		prev_x;
	int		prev_y;
}				t_file;

typedef struct s_txtr {
	void	*textr[5];
	int		textr_size;
	int		init_x;
	int		init_y;
	int		num_colls;
	int		num_exits;
	int		num_player;
}				t_txtr;

typedef struct s_data {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		endian;
	int		width;
	int		height;
	int		p_y_axis;
	int		p_x_axis;
	int		win_x;
	int		win_y;
	char	**matrix;
	int		map_x;
	int		map_y;
	int		num_movs;
	t_file	file;
	t_txtr	txtr;
}				t_data;

# endif