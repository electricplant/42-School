/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reqs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:41:45 by dgerhard          #+#    #+#             */
/*   Updated: 2024/24/07 17:04:41 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef REQS_H
# define REQS_H

# include "structs.h"
# include <stdio.h>
# include <stdlib.h>
# include "../minilibx-linux/mlx.h"
# include "get_next_line.h"
# include "paths.h"
# include <X11/X.h>
# include <fcntl.h>
# include <stdbool.h>

//main
int 	close_window(t_data *img);
int 	key_hook(int keycode, t_data *img);

//ft_parse
int 	ft_parse(t_data *img);
int		ft_fill_map(t_data *img);
int		init_matrix(t_data *img);
int		free_matrix(t_data *img);
int		ft_fill_line(t_data *img, int i);

//ft_display_map
int		ft_texture_paths(t_data *img);
void	ft_draw_scene(t_data *img);
void 	ft_move_player(t_data *img, int x, int y);
void	ft_put_texture(t_data *img, char dingus, int x, int y);
void	update_movements(t_data *img);

//ft_check_map
void	ft_verify_map(t_data *img, int x, int y);
void	ft_check_walls(t_data *img);
void	ft_check_textures(t_data *img);
t_data	make_deep_copy(t_data src);

//helpers
void	ft_putstr_fd(char *s, int fd);
void	print_nb(long nb, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);
int		ft_strlen(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_strcmp(const char *s1, const char *s2);

//utils
int		ft_check_exit(t_data *img, char p);
bool	check_file_type(int argc, char *argv);

//ft_error
int		ft_error(char *str, t_data *img);
void	ft_free_mlx(t_data *img);
#endif