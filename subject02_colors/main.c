#include "../subject.h"
#include <math.h> // Lembre-se de adicionar -lm no Makefile!

// Key codes for macOS
#define K_ESC 53
#define K_UP 126
#define K_DOWN 125
#define K_LEFT 123
#define K_RIGHT 124
// TODO: Defina o keycode para a tecla 'C'

// Mouse codes for macOS
#define M_SCROLL_UP 4
#define M_SCROLL_DOWN 5

static void my_mlx_pixel_put(t_data *d, int x, int y, int color)
{
    char    *dst;
    if (x < 0 || x >= d->w || y < 0 || y >= d->h) return;
    dst = d->addr + (y * d->line_length) + (x * (d->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

// TODO: Altere mandelbrot_iters para retornar os valores finais de zr e zi
// A nova assinatura será: int mandelbrot_iters(double cr, double ci, int max_iter, double *zr_out, double *zi_out)
int mandelbrot_iters(double cr, double ci, int max_iter)
{
    double zr = 0, zi = 0;
    int i = 0;
    while (i < max_iter)
    {
        double zr2 = zr*zr - zi*zi + cr;
        double zi2 = 2*zr*zi + ci;
        zr = zr2; zi = zi2;
        if (zr*zr + zi*zi > 4.0) break;
        i++;
    }
    return i;
}

// TODO: Altere color_from_iter para criar cores psicodélicas
// Use a técnica de "smooth coloring" e funções de seno.
// A nova assinatura será: int color_from_iter(int i, int max, t_data *d, double zr, double zi)
int color_from_iter(int i, int max)
{
    if (i == max) return 0x00000000;
    return (i * 255 / max) << 16; // Cor atual (gradiente vermelho)
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
            
            // TODO: Atualize as chamadas para mandelbrot_iters e color_from_iter
            int it = mandelbrot_iters(cr, ci, d->max_iter);
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

static int key_hook(int keycode, t_data *d)
{
	if (keycode == K_ESC)
		close_win(d);
	if (keycode == K_UP)
		d->shift_y -= 0.1 / d->zoom;
	if (keycode == K_DOWN)
		d->shift_y += 0.1 / d->zoom;
	if (keycode == K_LEFT)
		d->shift_x -= 0.1 / d->zoom;
	if (keycode == K_RIGHT)
		d->shift_x += 0.1 / d->zoom;
    // TODO: Adicione a verificação da tecla 'C' para alterar d->color_shift
	d->dirty = 1;
	return (0);
}

static int mouse_hook(int button, int x, int y, t_data *d)
{
	(void)x; (void)y;
	if (button == M_SCROLL_UP)
		d->zoom *= 1.1;
	if (button == M_SCROLL_DOWN)
		d->zoom /= 1.1;
	d->dirty = 1;
	return (0);
}

int main(void)
{
    t_data  d;
    d.w = 800; d.h = 800;
	d.zoom = 1.0;
	d.shift_x = -0.5; d.shift_y = 0.0;
	d.max_iter = 50;
    // TODO: Inicialize a nova variável d.color_shift
	d.dirty = 1;

    d.mlx = mlx_init();
    d.win = mlx_new_window(d.mlx, d.w, d.h, "Subject 02 - Colors");
    d.img = mlx_new_image(d.mlx, d.w, d.h);
    d.addr = mlx_get_data_addr(d.img, &d.bits_per_pixel, &d.line_length, &d.endian);

    mlx_hook(d.win, 17, 0, close_win, &d);
    mlx_key_hook(d.win, key_hook, &d);
    mlx_mouse_hook(d.win, mouse_hook, &d);
    mlx_loop_hook(d.mlx, loop_hook, &d);
    mlx_loop(d.mlx);
    return (0);
}