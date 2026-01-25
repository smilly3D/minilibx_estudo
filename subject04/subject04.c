#include "../minilibx-linux/mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>
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

static int	app_destroy(t_app *app)
{
	if (app->img.handle)
		mlx_destroy_image(app->mlx, app->img.handle);
	app->img.handle = NULL;
	if (app->win)
		mlx_destroy_window(app->mlx, app->win);
	app->win = NULL;
	if (app->mlx)
	{
		mlx_destroy_display(app->mlx);
		free(app->mlx);
		app->mlx = NULL;
	}
	exit(EXIT_SUCCESS);
	return (0);
}

/*
Starter file.

Meta: implementar primitivas no buffer:
- draw_line (Bresenham)
- draw_rect_fill
- draw_circle_fill

Faça aos poucos seguindo subject04.md.
*/

static void	draw_scene(t_app *app)
{
	/* TODO: limpar e desenhar uma cena usando suas primitivas */
	(void)app;
}

static int	on_keypress(int keysym, t_app *app)
{
	if (keysym == XK_Escape)
		app_destroy(app);
	return (0);
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
			"subject04 - starter");
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
