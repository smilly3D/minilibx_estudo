#include "../minilibx_opengl_20191021/mlx.h"
#include "../mlx_macos.h"
#include <stdlib.h>

typedef struct s_app
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
} 	t_app;

/*
Starter file.

Meta: entender como desenhar com mlx_pixel_put (lento) e cor 0xRRGGBB.

Tarefas principais estão em subject01.md.
*/

static int	rgb(int r, int g, int b)
{
	/* TODO: clamp 0..255 e retornar (r<<16)|(g<<8)|b */
	(void)r;
	(void)g;
	(void)b;
	return (0);
}

static int	app_destroy(t_app *app)
{
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
	/* TODO: desenhar um gradiente com mlx_pixel_put */
	/* TODO: desenhar um crosshair no centro */
	mlx_pixel_put(app->mlx, app->win, app->width / 2, app->height / 2,
		rgb(255, 0, 0));
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
			"subject01 - starter");
	if (!app.win)
		return (1);
	draw_scene(&app);
	mlx_hook(app.win, DestroyNotify, StructureNotifyMask, app_destroy, &app);
	mlx_hook(app.win, KeyPress, KeyPressMask, on_keypress, &app);
	mlx_loop(app.mlx);
	return (0);
}
