#include <stdio.h>
#include <stdlib.h>
//#include <../../Working/minilibx-linux/mlx.h>
#include <mlx.h>
int	main(void)
{
	void	*mlx;
	void	*img;
	char	*relative_path = "./test.xpm";
	int		img_width;
	int		img_height;

	mlx = mlx_init();
	// if (mlx == NULL)
	// {
	// 	printf("Error\n");
	// 	return (1);
	// }
	img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
	// if (img == NULL)
	// {
	// 	printf("Error\n");
	// 	return (1);
	// }


}
