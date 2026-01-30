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

// A função mandelbrot_iters agora retorna 'int'
// e não precisa dos ponteiros de saída zr_out e zi_out
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

// A função color_from_iter não precisa mais do ponteiro para t_data
// nem dos valores de zr e zi
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
            // Chamada atualizada para mandelbrot_iters
            int it = mandelbrot_iters(cr, ci, d->max_iter);
            // Chamada atualizada para color_from_iter
            int color = color_from_iter(it, d->max_iter);
            my_mlx_pixel_put(d, x, y, color);
            x++;
        }
        y++;
    }
}

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

// TODO: Crie a função 'key_hook' aqui.
// Ela deve receber um 'keycode' e um ponteiro para 't_data'.
// Use as setas para mudar 'shift_x' e 'shift_y'.
// Use ESC para chamar 'close_win'.
// Lembre-se de setar 'd->dirty = 1' após qualquer mudança.

// TODO: Crie a função 'mouse_hook' aqui.
// Ela deve receber 'button', 'x', 'y' e um ponteiro para 't_data'.
// Use o scroll up/down para aumentar/diminuir o 'zoom'.
// Lembre-se de setar 'd->dirty = 1'.

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

    d.win = mlx_new_window(d.mlx, d.w, d.h, "Subject 01 - Interaction");
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
    // TODO: Conecte os seus novos hooks aqui usando mlx_key_hook e mlx_mouse_hook.
    
    mlx_loop_hook(d.mlx, loop_hook, &d);
    mlx_loop(d.mlx);
    return (0);
}