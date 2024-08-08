/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:41:45 by dgerhard          #+#    #+#             */
/*   Updated: 2024/24/07 17:04:41 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reqs.h"

int	close_window(t_data *img)
{
	free_matrix(img);
	ft_free_mlx(img);
	exit(0);
}

int	key_hook(int keycode, t_data *img)
{
	if (keycode == 97)
		ft_move_player(img, -1, 0);
	if (keycode == 100)
		ft_move_player(img, 1, 0);
	if (keycode == 119)
		ft_move_player(img, 0, -1);
	if (keycode == 115)
		ft_move_player(img, 0, 1);
	if (keycode == 65307)
		close_window(img);
	return (0);
}

static void	init_vars(t_data *img)
{
	img->win_x = 0;
	img->win_y = 0;
	img->p_x_axis = 0;
	img->p_y_axis = 0;
	img->map_x = 0;
	img->map_y = 0;
	img->txtr.num_colls = 0;
	img->txtr.num_exits = 0;
	img->txtr.textr_size = 64;
	img->num_movs = 0;
	img->file.prev_x = 0;
	img->file.prev_y = 0;
	img->matrix = NULL;
	img->mlx = NULL;
	img->txtr.textr[0] = NULL;
	img->txtr.textr[1] = NULL;
	img->txtr.textr[2] = NULL;
	img->txtr.textr[3] = NULL;
	img->txtr.textr[4] = NULL;
}

int	main(int argc, char **argv)
{
	t_data	img;
	t_data	img2;

	if (argc != 2 || !(check_file_type(argv[1])))
		ft_error("You forgot to choose a map / bad filetype", &img);
	img.file.filename = argv[1];
	init_vars(&img);
	ft_parse(&img);
	init_matrix(&img);
	img2 = make_deep_copy(img);
	ft_verify_map(&img2, img.p_x_axis, img.p_y_axis);
	free_matrix(&img2);
	ft_check_textures(&img);
	img.mlx = mlx_init();
	if (img.mlx == NULL)
		ft_error("xlx_init failed\n", &img);
	ft_texture_paths(&img);
	img.win = mlx_new_window(img.mlx, img.win_x, img.win_y, "So Long");
	ft_draw_scene(&img);
	ft_move_player(&img, 0, 0);
	mlx_key_hook(img.win, key_hook, &img);
	mlx_hook(img.win, DestroyNotify, StructureNotifyMask, close_window, &img);
	mlx_loop(img.mlx);
}
