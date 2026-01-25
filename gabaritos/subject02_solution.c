#include "../minilibx-linux/mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_img
{
	void	*handle;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
} 	t_img;

typedef struct s_app
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	t_img	img;
} 	t_app;

static int	rgb(int r, int g, int b)
{
	if (r < 0) r = 0;
	if (g < 0) g = 0;
	if (b < 0) b = 0;
	if (r > 255) r = 255;
	if (g > 255) g = 255;
	if (b > 255) b = 255;
	return ((r << 16) | (g << 8) | b);
}

static void	img_put_pixel(t_img *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

static void	draw_gradient_img(t_app *app)
{
	int x;
	int y;

	y = 0;
	while (y < app->height)
	{
		x = 0;
		while (x < app->width)
		{
			int r = (x * 255) / (app->width - 1);
			int g = (y * 255) / (app->height - 1);
			int b = 128;
			img_put_pixel(&app->img, x, y, rgb(r, g, b));
			x++;
		}
		y++;
	}
}

static int	app_destroy(t_app *app)
{
	if (app->img.handle)
		mlx_destroy_image(app->mlx, app->img.handle);
	if (app->win)
		mlx_destroy_window(app->mlx, app->win);
	if (app->mlx)
	{
		mlx_destroy_display(app->mlx);
		free(app->mlx);
	}
	exit(EXIT_SUCCESS);
	return (0);
}

static int	on_keypress(int keysym, t_app *app)
{
	if (keysym == XK_Escape)
		return (app_destroy(app));
	return (0);
}

int	main(void)
{
	t_app app;

	app.width = 800;
	app.height = 600;
	app.img.handle = NULL;
	app.mlx = mlx_init();
	if (!app.mlx)
		return (1);
	app.win = mlx_new_window(app.mlx, app.width, app.height,
			"subject02 - image buffer");
	if (!app.win)
		return (1);
	app.img.handle = mlx_new_image(app.mlx, app.width, app.height);
	if (!app.img.handle)
		return (1);
	app.img.addr = mlx_get_data_addr(app.img.handle, &app.img.bpp,
			&app.img.line_len, &app.img.endian);
	draw_gradient_img(&app);
	mlx_put_image_to_window(app.mlx, app.win, app.img.handle, 0, 0);
	mlx_hook(app.win, DestroyNotify, 0, app_destroy, &app);
	mlx_hook(app.win, KeyPress, KeyPressMask, on_keypress, &app);
	mlx_loop(app.mlx);
	return (0);
}
