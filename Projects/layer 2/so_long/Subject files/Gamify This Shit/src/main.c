#include "reqs.h"

int close_window(t_data *img)
{
	mlx_destroy_window(img->mlx, img->win);
	exit(0);
}

void move_player(t_data *img)
{
	mlx_clear_window(img->mlx, img->win);
	mlx_put_image_to_window(img->mlx, img->win, img->img, img->p_x_axis, img->p_y_axis);
}

int key_hook(int keycode, t_data *img)
{
	if (keycode == 65361)
		img->p_x_axis -= 64;
	if (keycode == 65363)
		img->p_x_axis += 64;
	if (keycode == 65362)
		img->p_y_axis -= 64;
	if (keycode == 65364)
		img->p_y_axis += 64;
	if (keycode == 65307)
	{
		mlx_destroy_window(img->mlx, img->win);
		exit(0);
	}
	move_player(img);
	return (0);
}

int	main(void)
{
	char	*relative_path = "textures/./Player.xpm";
	t_data	img;
	int		x = 512;
	int		y = 512;
	img.p_x_axis = 0;
	img.p_y_axis = 0;

	img.mlx = mlx_init(); 
	if (img.mlx == NULL)
	{
		printf("Error, mlx_init failed\n");
		return (1);
	}

	#include <fcntl.h>

	int		fd;
	char	*line;

	fd = open("test.ber", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s\n", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);

	img.img = mlx_xpm_file_to_image(img.mlx, relative_path, &img.width, &img.height);
	if (img.img == NULL)
	{
		printf("Error, xpm_file_to_image failed :(\n");
		return (1);
	}
	//img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	img.win = mlx_new_window(img.mlx, x, y, "Tennis titties");
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	mlx_key_hook(img.win, key_hook, &img);
	mlx_hook(img.win, DestroyNotify, StructureNotifyMask, close_window, &img);
	mlx_loop(img.mlx);

}
