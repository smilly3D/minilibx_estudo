/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subject00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilly <smilly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:19:02 by smilly            #+#    #+#             */
/*   Updated: 2026/01/26 16:39:08 by smilly           ###   ########.fr       */
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

	   draw_rect_fill(d, d->rx, d->ry, d->rw, d->rh, 0x00FF0000); 

	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
}

static void update_rect(t_data *d)
{
    d->rx += d->vx;
    d->ry += d->vy;

    // Colisão com esquerda/direita
    if (d->rx < 0)
    {
        d->rx = 0;
        d->vx = -d->vx;
    }
    else if (d->rx + d->rw > d->w)
    {
        d->rx = d->w - d->rw;
        d->vx = -d->vx;
    }

    // Colisão com topo/base
    if (d->ry < 0)
    {
        d->ry = 0;
        d->vy = -d->vy;
    }
    else if (d->ry + d->rh > d->h)
    {
        d->ry = d->h - d->rh;
        d->vy = -d->vy;
    }
}

static int loop_hook(void *param)
{
    t_data *d;

    d = (t_data *)param;
    update_rect(d);
    render_scene(d);
    return (0);
}

int	key_press_vel(int keycode, void *param)
{
	t_data	*d = (t_data *)param;
	//vx
	if (keycode == 65361)
		d->vx -= 1; // esquerda
	if (keycode == 65363)
		d->vx += 1; // direita

	//vy	
	if (keycode == 65362)
		d->vy += 1;  // cima
	if (keycode == 65364)
		d->vy -= 1;  // baixo

	return (0);
}

int mouse_scroll_size(int button, int x, int y, void *param)
{
	t_data	*d = (t_data *)param;
	(void)x;
	(void)y;
	 if (button == 4) // zoom in
    {
		d->rw += 1;
		d->rh += 1;
	}
	 else if (button == 5) // zoom out
    {
		d->rw -= 1;
		d->rh -= 1;
	}
	return (0);
}

int close_win(void *param)
{
	t_data	*d = (t_data *)param;

	mlx_destroy_window(d->mlx, d->win);
    exit(0);
	return (0);
}

int	main(void)
{
	t_data	d;

	d.w = 800;
	d.h = 800;
	// d.zoom = 1.0;
	// d.offset_x = 0.0;
	// d.offset_y = 0.0;
	// d.max_iter = 50;

	d.mlx = mlx_init();
	if (!d.mlx)
		return (1);

	d.win = mlx_new_window(d.mlx, d.w, d.h, "hooks demo");
	if (!d.win)
		return (1);

	d.img = mlx_new_image(d.mlx, d.w, d.h);
	if (!d.img)
		return (1);

	d.addr = mlx_get_data_addr(d.img,
			&d.bits_per_pixel, &d.line_length, &d.endian);
	if (!d.addr)
		return (1);

	// conecte os hooks no seu projeto do retângulo
	// faça:
	// setas mudam vx/vy
	mlx_key_hook(d.win, key_press_vel, &d);
	// scroll do mouse muda o tamanho do retângulo (rw/rh)
	mlx_mouse_hook(d.win, mouse_scroll_size, &d);
	// ESC fecha
   mlx_hook(d.win, 17, 0, close_win, &d);

	    // Estado inicial do retângulo
    d.rw = 120;
    d.rh = 80;
    d.rx = 10;
    d.ry = 10;
    d.vx = 3;   // velocidade (pixels por frame)
    d.vy = 2;
	
	mlx_loop_hook(d.mlx, loop_hook, &d);
	mlx_loop(d.mlx);
	return (0);
}
