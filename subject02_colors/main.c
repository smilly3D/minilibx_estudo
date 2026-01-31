/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilly <smilly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 20:01:32 by smilly            #+#    #+#             */
/*   Updated: 2026/01/30 20:10:08 by smilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../subject.h"
#include <math.h>

static void	my_mlx_pixel_put(t_data *d, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= d->w || y < 0 || y >= d->h)
		return ;

	dst = d->addr
		+ (y * d->line_length)
		+ (x * (d->bits_per_pixel / 8));

	*(unsigned int *)dst = color;
}

int	mandelbrot_iters(double cr, double ci, int max_iter,
					double *zr_out, double *zi_out)
{
	double	zr;
	double	zi;
	int		i;
	double	zr2;
	double	zi2;

	zr = 0;
	zi = 0;
	i = 0;
	while (i < max_iter)
	{
		zr2 = zr * zr - zi * zi + cr;
		zi2 = 2 * zr * zi + ci;
		zr = zr2;
		zi = zi2;
		if (zr * zr + zi * zi > 4.0)
			break ;
		i++;
	}
	*zr_out = zr;
	*zi_out = zi;
	return (i);
}

// Smooth coloring algorithm
int	color_from_iter(int i, int max, t_data *d, double zr, double zi)
{
	double	smooth_i;
	int		r;
	int		g;
	int		b;

	if (i == max)
		return (0x000000);

	smooth_i = i + 1 - log(log(sqrt(zr * zr + zi * zi))) / log(2.0);

	r = (int)(sin(0.1 * smooth_i + d->color_shift) * 127 + 128);
	g = (int)(sin(0.1 * smooth_i + d->color_shift + 2) * 127 + 128);
	b = (int)(sin(0.1 * smooth_i + d->color_shift + 4) * 127 + 128);

	return ((r << 16) | (g << 8) | b);
}

static void render_fractal(t_data *d)
{
	int x, y;
	double scale = 4.0 / (double)(d->w < d->h ? d->w : d->h);

	y = 0;
	while (y < d->h)
	{
		x = 0;
		while (x < d->w)
		{
			double cr = (x - d->w/2.0) * scale / d->zoom + d->shift_x;
			double ci = (y - d->h/2.0) * scale / d->zoom + d->shift_y;
			
			double zr, zi;
			int it = mandelbrot_iters(cr, ci, d->max_iter, &zr, &zi);
			int color = color_from_iter(it, d->max_iter, d, zr, zi);

			my_mlx_pixel_put(d, x, y, color);
			x++;
		}
		y++;
	}
}

static int	loop_hook(void *param)
{
	t_data	*d;

	d = (t_data *)param;
	if (d->dirty)
	{
		render_fractal(d);
		mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
		d->dirty = 0;
	}
	return (0);
}

int	close_win(void *param)
{
	t_data	*d;

	d = (t_data *)param;
	mlx_destroy_window(d->mlx, d->win);
	exit(0);
	return (0);
}

static int	key_hook(int keycode, t_data *d)
{
	if (keycode == KEY_ESC)
		close_win(d);
	if (keycode == KEY_UP)
		d->shift_y -= 0.1 / d->zoom;
	if (keycode == KEY_DOWN)
		d->shift_y += 0.1 / d->zoom;
	if (keycode == KEY_LEFT)
		d->shift_x -= 0.1 / d->zoom;
	if (keycode == KEY_RIGHT)
		d->shift_x += 0.1 / d->zoom;
	if (keycode == KEY_C)
		d->color_shift += 0.5;
	d->dirty = 1;
	return (0);
}

static int	mouse_hook(int button, int x, int y, t_data *d)
{
	(void)x;
	(void)y;
	if (button == SCROLL_UP)
		d->zoom *= 1.1;
	if (button == SCROLL_DOWN)
		d->zoom /= 1.1;
	d->dirty = 1;
	return (0);
}

int main(void)
{
	t_data	d;

	d.w = 800;
	d.h = 800;
	d.zoom = 1.0;
	d.shift_x = -0.5;
	d.shift_y = 0.0;
	d.max_iter = 50;
	d.color_shift = 0.0;
	d.dirty = 1;

	d.mlx = mlx_init();
	if (!d.mlx)
		return (1);

	d.win = mlx_new_window(d.mlx, d.w, d.h, "Subject 02 - Colors");
	if (!d.win)
		return (1);

	d.img = mlx_new_image(d.mlx, d.w, d.h);
	if (!d.img)
		return (1);

	d.addr = mlx_get_data_addr(d.img,
			&d.bits_per_pixel, &d.line_length, &d.endian);
	if (!d.addr)
		return (1);

	mlx_hook(d.win, 17, 0, close_win, &d);
	mlx_key_hook(d.win, key_hook, &d);
	mlx_mouse_hook(d.win, mouse_hook, &d);

	mlx_loop_hook(d.mlx, loop_hook, &d);
	mlx_loop(d.mlx);
	return (0);
}
