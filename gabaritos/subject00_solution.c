#include "../minilibx-linux/mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_app
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
} 	t_app;

static int	app_destroy(t_app *app)
{
	if (!app)
		exit(EXIT_FAILURE);
	if (app->win)
	{
		mlx_destroy_window(app->mlx, app->win);
		app->win = NULL;
	}
	if (app->mlx)
	{
		mlx_destroy_display(app->mlx);
		free(app->mlx);
		app->mlx = NULL;
	}
	exit(EXIT_SUCCESS);
	return (0);
}

static int	on_keypress(int keysym, t_app *app)
{
	if (keysym == XK_Escape)
		return (app_destroy(app));
	if (keysym == XK_space)
		printf("space!\n");
	return (0);
}

static void	app_init(t_app *app)
{
	app->width = 800;
	app->height = 600;
	app->mlx = mlx_init();
	if (!app->mlx)
	{
		fprintf(stderr, "mlx_init failed\n");
		exit(EXIT_FAILURE);
	}
	app->win = mlx_new_window(app->mlx, app->width, app->height,
			"subject00 - hello mlx");
	if (!app->win)
	{
		fprintf(stderr, "mlx_new_window failed\n");
		app_destroy(app);
	}
}

int	main(void)
{
	t_app	app;

	app.mlx = NULL;
	app.win = NULL;
	app_init(&app);
	mlx_hook(app.win, DestroyNotify, 0, app_destroy, &app);
	mlx_hook(app.win, KeyPress, KeyPressMask, on_keypress, &app);
	mlx_loop(app.mlx);
	return (0);
}
