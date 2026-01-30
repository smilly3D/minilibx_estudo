#ifndef SUBJECT_H
#define SUBJECT_H

# include <unistd.h>
# include <stdlib.h> 
# include <stdio.h>
# include "minilibx_opengl_20191021/mlx.h"
# include "mlx_macos.h"

// typedef struct s_data
// {
// 	void	*mlx;
// 	void	*win;
// 	void	*img;
// 	char	*addr;
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;
// 	int		w;
// 	int		h;

// 	int		rx;
// 	int		ry;
// 	int		vx;
// 	int		vy;
// 	int		rw;
// 	int		rh;
// } 			t_data;

typedef struct s_data {
	void *mlx; void *win;
	void *img; char *addr;
	int bits_per_pixel; int line_length; int endian;
	int w, h;

	double zoom;
	double shift_x;
	double shift_y;
	int max_iter;

	int fractal;		// 0=mandelbrot, 1=julia, 2=burning_ship...
	double julia_re;
	double julia_im;

	int dirty;			// flag: precisa redesenhar
	double color_shift;	// deslocamento para mudar as cores
} t_data;

#endif
