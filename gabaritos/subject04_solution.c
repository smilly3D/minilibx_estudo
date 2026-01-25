#include "../minilibx-linux/mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <stdlib.h>
#include <math.h>

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

static void	img_put_pixel(t_app *app, int x, int y, int color)
{
	char *dst;

	if (x < 0 || y < 0 || x >= app->width || y >= app->height)
		return ;
	dst = app->img.addr + (y * app->img.line_len + x * (app->img.bpp / 8));
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
			img_put_pixel(app, x, y, color);
			x++;
		}
		y++;
	}
}

static int	abs_i(int n)
{
	return (n < 0 ? -n : n);
}

static void	draw_line(t_app *app, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs_i(x1 - x0);
	int sx = (x0 < x1) ? 1 : -1;
	int dy = -abs_i(y1 - y0);
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx + dy;

	while (1)
	{
		img_put_pixel(app, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break ;
		int e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

static void	draw_rect_fill(t_app *app, int x, int y, int w, int h, int color)
{
	int ix;
	int iy;

	iy = 0;
	while (iy < h)
	{
		ix = 0;
		while (ix < w)
		{
			img_put_pixel(app, x + ix, y + iy, color);
			ix++;
		}
		iy++;
	}
}

static void	draw_circle_fill(t_app *app, int cx, int cy, int radius, int color)
{
	int x;
	int y;

	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if ((x * x + y * y) <= radius * radius)
				img_put_pixel(app, cx + x, cy + y, color);
			x++;
		}
		y++;
	}
}

static void	draw_scene(t_app *app)
{
	img_clear(app, rgb(18, 18, 24));
	draw_rect_fill(app, 80, 80, 220, 140, rgb(60, 120, 220));
	draw_circle_fill(app, 520, 220, 80, rgb(240, 90, 90));
	draw_line(app, 40, 520, 760, 520, rgb(255, 255, 255));
	draw_line(app, 40, 520, 400, 320, rgb(255, 255, 255));
	draw_line(app, 400, 320, 760, 520, rgb(255, 255, 255));
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
			"subject04 - primitives");
	if (!app.win)
		return (1);
	app.img.handle = mlx_new_image(app.mlx, app.width, app.height);
	if (!app.img.handle)
		return (1);
	app.img.addr = mlx_get_data_addr(app.img.handle, &app.img.bpp,
			&app.img.line_len, &app.img.endian);
	draw_scene(&app);
	mlx_put_image_to_window(app.mlx, app.win, app.img.handle, 0, 0);
	mlx_hook(app.win, DestroyNotify, 0, app_destroy, &app);
	mlx_hook(app.win, KeyPress, KeyPressMask, on_keypress, &app);
	mlx_loop(app.mlx);
	return (0);
}
