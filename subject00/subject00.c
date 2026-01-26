/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subject00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilly <smilly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:19:02 by smilly            #+#    #+#             */
/*   Updated: 2026/01/26 15:22:00 by smilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../subject.h"

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

static void	clear_image(t_data *d, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < d->h)
	{
		x = 0;
		while (x < d->w)
		{
			my_mlx_pixel_put(d, x, y, color);
			x++;
		}
		y++;
	}
}

static void	clear_image_fast(t_data *d, int color)
{
	int	x;
	int	y;
	int	*row;
	int	pixels_per_row;

	pixels_per_row = d->line_length / 4;

	y = 0;
	while (y < d->h)
	{
		row = (int *)(d->addr + y * d->line_length);
		x = 0;
		while (x < pixels_per_row)
		{
			row[x] = color;
			x++;
		}
		y++;
	}
}

static void	clear_image_auto(t_data *d, int color)
{
	if (d->bits_per_pixel == 32)
		clear_image_fast(d, color);
	else
		clear_image(d, color);
}

static void draw_rect_fill(t_data *d, int x, int y, int w, int h, int color)
{
	int xx;
	int yy;

	yy = 0;
	while (yy < h)
	{
		xx = 0;
		while (xx < w)
		{
			my_mlx_pixel_put(d, x + xx, y + yy, color);
			xx++;
		}
		yy++;
	}
}

static void	render_scene(t_data *d)
{

	clear_image_auto(d, 0x00000000);

	draw_rect_fill(d, 100, 100, 200, 120, 0x0000FF00); // retângulo verde

	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
}

static int	loop_hook(void *param)
{
	t_data	*d;

	d = (t_data *)param;
	render_scene(d);
	return (0);
}

int	main(void)
{
	t_data	d;

	d.w = 800;
	d.h = 800;

	d.mlx = mlx_init();
	if (!d.mlx)
		return (1);

	d.win = mlx_new_window(d.mlx, d.w, d.h, "hello world!");
	if (!d.win)
		return (1);

	d.img = mlx_new_image(d.mlx, d.w, d.h);
	if (!d.img)
		return (1);

	d.addr = mlx_get_data_addr(d.img,
			&d.bits_per_pixel, &d.line_length, &d.endian);
	if (!d.addr)
		return (1);

	mlx_loop_hook(d.mlx, loop_hook, &d);
	mlx_loop(d.mlx);
	return (0);
}
