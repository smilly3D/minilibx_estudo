#include "../minilibx-linux/mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
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
	int		brush;
	int		color;
	int		painting;
	int		bg;
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

static void	draw_brush(t_app *app, int cx, int cy)
{
	int x;
	int y;
	int r = app->brush;

	y = -r;
	while (y <= r)
	{
		x = -r;
		while (x <= r)
		{
			if ((x * x + y * y) <= r * r)
				img_put_pixel(app, cx + x, cy + y, app->color);
			x++;
		}
		y++;
	}
}

static int	write_all(int fd, const void *buf, size_t len)
{
	size_t off;
	ssize_t w;

	off = 0;
	while (off < len)
	{
		w = write(fd, (const char *)buf + off, len - off);
		if (w <= 0)
			return (-1);
		off += (size_t)w;
	}
	return (0);
}

static int	save_ppm(t_app *app, const char *path)
{
	int fd;
	int x;
	int y;
	char header[64];
	int header_len;

	fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		return (-1);
	header_len = snprintf(header, sizeof(header), "P6\n%d %d\n255\n",
			app->width, app->height);
	if (header_len <= 0 || (size_t)header_len >= sizeof(header))
		return (close(fd), -1);
	if (write_all(fd, header, (size_t)header_len) != 0)
		return (close(fd), -1);
	y = 0;
	while (y < app->height)
	{
		x = 0;
		while (x < app->width)
		{
			char *dst = app->img.addr
				+ (y * app->img.line_len + x * (app->img.bpp / 8));
			unsigned int c = *(unsigned int *)dst;
			unsigned char px[3];
			px[0] = (c >> 16) & 0xFF;
			px[1] = (c >> 8) & 0xFF;
			px[2] = c & 0xFF;
			if (write_all(fd, px, 3) != 0)
				return (close(fd), -1);
			x++;
		}
		y++;
	}
	close(fd);
	return (0);
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
	if (keysym == XK_s)
		save_ppm(app, "output.ppm");
	return (0);
}

static int	on_mousedown(int button, int x, int y, t_app *app)
{
	if (button == Button1)
	{
		app->painting = 1;
		draw_brush(app, x, y);
	}
	else if (button == Button3)
		img_clear(app, app->bg);
	else if (button == Button4)
		app->brush += 2;
	else if (button == Button5)
		app->brush -= 2;
	if (app->brush < 2)
		app->brush = 2;
	if (app->brush > 80)
		app->brush = 80;
	return (0);
}

static int	on_mouseup(int button, int x, int y, t_app *app)
{
	(void)x;
	(void)y;
	if (button == Button1)
		app->painting = 0;
	return (0);
}

static int	on_mousemove(int x, int y, t_app *app)
{
	if (app->painting)
		draw_brush(app, x, y);
	return (0);
}

static int	on_frame(t_app *app)
{
	mlx_put_image_to_window(app->mlx, app->win, app->img.handle, 0, 0);
	mlx_string_put(app->mlx, app->win, 10, 20, rgb(255, 255, 255),
		"LMB: paint | RMB: clear | wheel: brush | S: save | ESC: quit");
	return (0);
}

int	main(void)
{
	t_app app;

	app.width = 900;
	app.height = 600;
	app.brush = 12;
	app.bg = rgb(12, 12, 16);
	app.color = rgb(255, 200, 40);
	app.painting = 0;
	app.img.handle = NULL;
	app.mlx = mlx_init();
	if (!app.mlx)
		return (1);
	app.win = mlx_new_window(app.mlx, app.width, app.height,
			"subject06 - paint");
	if (!app.win)
		return (1);
	app.img.handle = mlx_new_image(app.mlx, app.width, app.height);
	if (!app.img.handle)
		return (1);
	app.img.addr = mlx_get_data_addr(app.img.handle, &app.img.bpp,
			&app.img.line_len, &app.img.endian);
	img_clear(&app, app.bg);

	mlx_hook(app.win, DestroyNotify, 0, app_destroy, &app);
	mlx_hook(app.win, KeyPress, KeyPressMask, on_keypress, &app);
	mlx_hook(app.win, ButtonPress, ButtonPressMask, on_mousedown, &app);
	mlx_hook(app.win, ButtonRelease, ButtonReleaseMask, on_mouseup, &app);
	mlx_hook(app.win, MotionNotify, PointerMotionMask, on_mousemove, &app);
	mlx_loop_hook(app.mlx, on_frame, &app);
	mlx_loop(app.mlx);
	return (0);
}
