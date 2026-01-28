#include "../minilibx_opengl_20191021/mlx.h"
#include "../mlx_macos.h"
#include <stdlib.h>

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

/*
Starter file.

Meta: desenhar em buffer (imagem) com:
- mlx_new_image
- mlx_get_data_addr
- mlx_put_image_to_window
*/

static void	img_put_pixel(t_img *img, int x, int y, int color)
{
	/* TODO: calcular o endereço do pixel usando line_len e bpp */
	(void)img;
	(void)x;
	(void)y;
	(void)color;
}

static int	app_destroy(t_app *app)
{
	if (app->img.handle)
		mlx_destroy_image(app->mlx, app->img.handle);
	app->img.handle = NULL;
	if (app->win)
		mlx_destroy_window(app->mlx, app->win);
	app->win = NULL;
	app->mlx = NULL;
	exit(EXIT_SUCCESS);
	return (0);
}

static int	on_keypress(int keysym, t_app *app)
{
	if (keysym == XK_Escape)
		app_destroy(app);
	return (0);
}

static void	draw_scene(t_app *app)
{
	/* TODO: desenhar algo no buffer, ex.: tabuleiro 8x8 */
	img_put_pixel(&app->img, app->width / 2, app->height / 2, 0x00FF00);
}

int	main(void)
{
	t_app app;

	app.width = 800;
	app.height = 600;
	app.mlx = mlx_init();
	if (!app.mlx)
		return (1);
	app.win = mlx_new_window(app.mlx, app.width, app.height,
			"subject02 - starter");
	if (!app.win)
		return (1);
	app.img.handle = mlx_new_image(app.mlx, app.width, app.height);
	if (!app.img.handle)
		return (1);
	app.img.addr = mlx_get_data_addr(app.img.handle, &app.img.bpp,
			&app.img.line_len, &app.img.endian);

	draw_scene(&app);
	mlx_put_image_to_window(app.mlx, app.win, app.img.handle, 0, 0);
	mlx_hook(app.win, DestroyNotify, StructureNotifyMask, app_destroy, &app);
	mlx_hook(app.win, KeyPress, KeyPressMask, on_keypress, &app);
	mlx_loop(app.mlx);
	return (0);
}
