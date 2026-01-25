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
	int		x;
	int		y;
	int		size;
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

static void	img_clear(t_app *app, int color)
{
	int x;
	int y;

	y = 0;
	while (y < app->height)
	{
		x = 0;
		while (x < app->width)
		{
			img_put_pixel(&app->img, x, y, color);
			x++;
		}
		y++;
	}
}

static void	draw_square(t_app *app)
{
	int x;
	int y;

	y = 0;
	while (y < app->size)
	{
		x = 0;
		while (x < app->size)
		{
			int px = app->x + x;
			int py = app->y + y;
			if (px >= 0 && px < app->width && py >= 0 && py < app->height)
				img_put_pixel(&app->img, px, py, rgb(255, 180, 0));
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
	if (keysym == XK_Left)
		app->x -= 10;
	else if (keysym == XK_Right)
		app->x += 10;
	else if (keysym == XK_Up)
		app->y -= 10;
	else if (keysym == XK_Down)
		app->y += 10;
	return (0);
}

static int	on_mousedown(int button, int x, int y, t_app *app)
{
	(void)button;
	app->x = x - app->size / 2;
	app->y = y - app->size / 2;
	return (0);
}

static int	on_frame(t_app *app)
{
	img_clear(app, rgb(20, 20, 30));
	draw_square(app);
	mlx_put_image_to_window(app->mlx, app->win, app->img.handle, 0, 0);
	return (0);
}

int	main(void)
{
	t_app app;

	app.width = 800;
	app.height = 600;
	app.size = 60;
	app.x = app.width / 2 - app.size / 2;
	app.y = app.height / 2 - app.size / 2;
	app.img.handle = NULL;
	app.mlx = mlx_init();
	if (!app.mlx)
		return (1);
	app.win = mlx_new_window(app.mlx, app.width, app.height,
			"subject03 - events + loop_hook");
	if (!app.win)
		return (1);
	app.img.handle = mlx_new_image(app.mlx, app.width, app.height);
	if (!app.img.handle)
		return (1);
	app.img.addr = mlx_get_data_addr(app.img.handle, &app.img.bpp,
			&app.img.line_len, &app.img.endian);
	mlx_hook(app.win, DestroyNotify, 0, app_destroy, &app);
	mlx_hook(app.win, KeyPress, KeyPressMask, on_keypress, &app);
	mlx_hook(app.win, ButtonPress, ButtonPressMask, on_mousedown, &app);
	mlx_loop_hook(app.mlx, on_frame, &app);
	mlx_loop(app.mlx);
	return (0);
}
