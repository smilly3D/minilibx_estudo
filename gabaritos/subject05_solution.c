#include "../minilibx-linux/mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
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
	double	x;
	double	y;
	double	vx;
	double	vy;
	int		radius;
	long	last_ns;
	double	fps;
	int		paused;
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

static long	now_ns(void)
{
	struct timespec ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ((long)ts.tv_sec * 1000000000L + ts.tv_nsec);
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
	if (keysym == XK_p)
		app->paused = !app->paused;
	return (0);
}

static void	update_physics(t_app *app, double dt)
{
	if (app->paused)
		return ;
	app->x += app->vx * dt;
	app->y += app->vy * dt;
	if (app->x - app->radius < 0)
	{
		app->x = app->radius;
		app->vx *= -1.0;
	}
	if (app->x + app->radius >= app->width)
	{
		app->x = app->width - app->radius - 1;
		app->vx *= -1.0;
	}
	if (app->y - app->radius < 0)
	{
		app->y = app->radius;
		app->vy *= -1.0;
	}
	if (app->y + app->radius >= app->height)
	{
		app->y = app->height - app->radius - 1;
		app->vy *= -1.0;
	}
}

static int	on_frame(t_app *app)
{
	long now = now_ns();
	double dt = (double)(now - app->last_ns) / 1000000000.0;

	if (dt <= 0.0)
		dt = 0.000001;
	app->last_ns = now;
	app->fps = 1.0 / dt;
	update_physics(app, dt);

	img_clear(app, rgb(10, 10, 14));
	draw_circle_fill(app, (int)round(app->x), (int)round(app->y), app->radius,
		rgb(120, 220, 160));
	mlx_put_image_to_window(app->mlx, app->win, app->img.handle, 0, 0);

	char hud[128];
	snprintf(hud, sizeof(hud), "fps: %.1f | p: pause | esc: quit", app->fps);
	mlx_string_put(app->mlx, app->win, 10, 20, rgb(255, 255, 255), hud);
	return (0);
}

int	main(void)
{
	t_app app;

	app.width = 800;
	app.height = 600;
	app.radius = 18;
	app.x = app.width / 2.0;
	app.y = app.height / 2.0;
	app.vx = 220.0;
	app.vy = 170.0;
	app.paused = 0;
	app.last_ns = now_ns();
	app.img.handle = NULL;
	app.mlx = mlx_init();
	if (!app.mlx)
		return (1);
	app.win = mlx_new_window(app.mlx, app.width, app.height,
			"subject05 - animation + dt");
	if (!app.win)
		return (1);
	app.img.handle = mlx_new_image(app.mlx, app.width, app.height);
	if (!app.img.handle)
		return (1);
	app.img.addr = mlx_get_data_addr(app.img.handle, &app.img.bpp,
			&app.img.line_len, &app.img.endian);
	mlx_hook(app.win, DestroyNotify, 0, app_destroy, &app);
	mlx_hook(app.win, KeyPress, KeyPressMask, on_keypress, &app);
	mlx_loop_hook(app.mlx, on_frame, &app);
	mlx_loop(app.mlx);
	return (0);
}
