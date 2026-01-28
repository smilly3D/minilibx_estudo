#ifndef SUBJECT_H
#define SUBJECT_H

#include "minilibx_opengl_20191021/mlx.h"

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		w;
	int		h;
} 			t_data;

#endif
