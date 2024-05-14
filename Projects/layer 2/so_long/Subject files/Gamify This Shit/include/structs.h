#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_data {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	int		p_y_axis;
	int		p_x_axis;
}				t_data;

#endif