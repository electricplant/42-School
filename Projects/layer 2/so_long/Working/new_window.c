#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <X11/X.h>

typedef struct s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int close_window(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}

int key_hook(int keycode, t_vars *vars)
{
	printf("keycode: %d\n", keycode);
	if (keycode == 65307)
		mlx_destroy_window(vars->mlx, vars->win);
	exit (0);
}

int main()
{
	t_vars vars;
	t_data img;
	int x = 500;
	int y = 500;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, x, y, "Weenie!");
	img.img = mlx_new_image(vars.mlx, x, y);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, DestroyNotify, StructureNotifyMask, close_window, &vars);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_loop(vars.mlx);
}

//compile line: gcc -o new_window new_window.c -L./minilibx-linux -lmlx -lXext -lX11 -I./minilibx-linux