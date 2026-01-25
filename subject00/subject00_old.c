#include "../minilibx-linux/mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>
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

Meta: implementar o ciclo de vida correto.

Checklist do subject00:
1) init: mlx_init + mlx_new_window
2) hooks: DestroyNotify + KeyPress (ESC)
3) cleanup: destroy window + destroy display + free(mlx)

Veja o guia em subject00.md.
*/

static int	app_destroy(t_app *app)
{
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
			"subject00 - starter");
	if (!app.win)
		return (1);

	mlx_hook(app.win, DestroyNotify, StructureNotifyMask, app_destroy, &app);
	mlx_hook(app.win, KeyPress, KeyPressMask, on_keypress, &app);

	mlx_loop(app.mlx);
	return (0);
}
