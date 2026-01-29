
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

static void my_mlx_pixel_put(t_data *d, int x, int y, int color)
{
    char    *dst;

    if (x < 0 || x >= d->w || y < 0 || y >= d->h)
        return ;

    dst = d->addr
        + (y * d->line_length)
        + (x * (d->bits_per_pixel / 8));

    *(unsigned int *)dst = color;
}

// static void clear_image(t_data *d, int color)
// {
//     int x;
//     int y;

//     y = 0;
//     while (y < d->h)
//     {
//         x = 0;
//         while (x < d->w)
//         {
//             my_mlx_pixel_put(d, x, y, color);
//             x++;
//         }
//         y++;
//     }
// }

// static void clear_image_fast(t_data *d, int color)
// {
//     int x;
//     int y;
//     int *row;
//     int pixels_per_row;

//     pixels_per_row = d->line_length / 4;

//     y = 0;
//     while (y < d->h)
//     {
//         row = (int *)(d->addr + y * d->line_length);
//         x = 0;
//         while (x < pixels_per_row)
//         {
//             row[x] = color;
//             x++;
//         }
//         y++;
//     }
// }

// static void clear_image_auto(t_data *d, int color)
// {
//     if (d->bits_per_pixel == 32)
//         clear_image_fast(d, color);
//     else
//         clear_image(d, color);
// }

int mandelbrot_iters(double cr, double ci, int max_iter)
{
    double zr = 0, zi = 0;
    int i = 0;
    while (i < max_iter)
    {
        double zr2 = zr*zr - zi*zi + cr;
        double zi2 = 2*zr*zi + ci;
        zr = zr2; zi = zi2;
        if (zr*zr + zi*zi > 4.0)
            break;
        i++;
    }
    return i;
}


int color_from_iter(int i, int max)
{
    if (i == max) return 0x00000000;
    return (i * 255 / max) << 16; // gradiente no vermelho
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
            int it = mandelbrot_iters(cr, ci, d->max_iter);
            int color = color_from_iter(it, d->max_iter);
            my_mlx_pixel_put(d, x, y, color);
            x++;
        }
        y++;
    }
}


// static void render_scene(t_data *d)
// {

//     clear_image_auto(d, 0x00000000);

//     render_fractal(d); 

//     mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
// }

static int loop_hook(void *param)
{
    t_data *d = param;

    if (d->dirty)
    {
        render_fractal(d);
        mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
        d->dirty = 0;
    }
    return 0;
}

int close_win(void *param)
{
    t_data  *d = (t_data *)param;

    mlx_destroy_window(d->mlx, d->win);
    exit(0);
    return (0);
}

int main(void)
{
    t_data  d;

    d.w = 800;
    d.h = 800;
	d.zoom = 1.0;
	d.shift_x = -0.5;
	d.shift_y = 0.0;
	d.max_iter = 50;
	d.dirty = 1;

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
    // mlx_key_hook(d.win, key_press_vel, &d);
    // scroll do mouse muda o tamanho do retângulo (rw/rh)
    // mlx_mouse_hook(d.win, mouse_scroll_size, &d);
    // ESC fecha
   mlx_hook(d.win, 17, 0, close_win, &d);
    
    mlx_loop_hook(d.mlx, loop_hook, &d);
    mlx_loop(d.mlx);
    return (0);
}

