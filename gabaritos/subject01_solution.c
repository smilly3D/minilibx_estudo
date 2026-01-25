#include "../minilibx-linux/mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_app
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
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

static int	app_destroy(t_app *app)
{
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

static void	draw_gradient(t_app *app)
{
	int x;
	int y;
	int cx = app->width / 2;
	int cy = app->height / 2;

	y = 0;
	while (y < app->height)
	{
		x = 0;
		while (x < app->width)
		{
			int r = (x * 255) / (app->width - 1);
			int g = (y * 255) / (app->height - 1);
			int b = 64;
			mlx_pixel_put(app->mlx, app->win, x, y, rgb(r, g, b));
			x++;
		}
		y++;
	}

	x = 0;
	while (x < app->width)
	{
		mlx_pixel_put(app->mlx, app->win, x, cy, rgb(255, 255, 255));
		x++;
	}
	y = 0;
	while (y < app->height)
	{
		mlx_pixel_put(app->mlx, app->win, cx, y, rgb(255, 255, 255));
		y++;
	}
}

int	main(void)
{
	t_app app;

	app.width = 800;
	app.height = 600;
	app.mlx = mlx_init();
	if (!app.mlx)
		return (1);
	app.win = mlx_new_window(app.mlx, app.width, app.height,
			"subject01 - pixel_put");
	if (!app.win)
		return (1);
	draw_gradient(&app);
	mlx_hook(app.win, DestroyNotify, 0, app_destroy, &app);
	mlx_hook(app.win, KeyPress, KeyPressMask, on_keypress, &app);
	mlx_loop(app.mlx);
	return (0);
}
