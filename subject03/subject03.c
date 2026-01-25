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
	int		x;
	int		y;
	int		size;
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

Meta: eventos + estado + loop hook.

Objetivo do subject03:
- guardar estado (posição, tamanho)
- mudar estado em callbacks (teclado/mouse)
- redesenhar tudo no on_frame (mlx_loop_hook)
*/

static int	on_keypress(int keysym, t_app *app)
{
	/* TODO: mover o quadrado com setas (ou WASD) */
	/* TODO: ESC fecha */
	if (keysym == XK_Escape)
		app_destroy(app);
	return (0);
}

static int	on_mousedown(int button, int x, int y, t_app *app)
{
	/* TODO: clique teleporta o quadrado para o mouse */
	(void)button;
	(void)x;
	(void)y;
	(void)app;
	return (0);
}

static int	on_frame(t_app *app)
{
	/* TODO: limpar o buffer, desenhar o quadrado, e dar put_image */
	(void)app;
	return (0);
}

int	main(void)
{
	t_app app;

	app.width = 800;
	app.height = 600;
	app.size = 60;
	app.x = 100;
	app.y = 100;
	app.mlx = mlx_init();
	if (!app.mlx)
		return (1);
	app.win = mlx_new_window(app.mlx, app.width, app.height,
			"subject03 - starter");
	if (!app.win)
		return (1);
	app.img.handle = mlx_new_image(app.mlx, app.width, app.height);
	if (!app.img.handle)
		return (1);
	app.img.addr = mlx_get_data_addr(app.img.handle, &app.img.bpp,
			&app.img.line_len, &app.img.endian);

	mlx_hook(app.win, DestroyNotify, StructureNotifyMask, app_destroy, &app);
	mlx_hook(app.win, KeyPress, KeyPressMask, on_keypress, &app);
	mlx_hook(app.win, ButtonPress, ButtonPressMask, on_mousedown, &app);
	mlx_loop_hook(app.mlx, on_frame, &app);
	mlx_loop(app.mlx);
	return (0);
}
