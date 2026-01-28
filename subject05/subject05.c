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
	/* TODO: pos, vel, last_time, paused, etc */
} 	t_app;

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

/*
Starter file.

Meta: fazer animação com dt (delta time) + loop_hook.

Sugestão: comece só desenhando algo estático e depois coloque dt.
*/

static int	on_frame(t_app *app)
{
	/* TODO: calcular dt, atualizar estado, desenhar frame */
	(void)app;
	return (0);
}

static int	on_keypress(int keysym, t_app *app)
{
	/* TODO: ESC fecha | P pausa */
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
			"subject05 - starter");
	if (!app.win)
		return (1);
	app.img.handle = mlx_new_image(app.mlx, app.width, app.height);
	if (!app.img.handle)
		return (1);
	app.img.addr = mlx_get_data_addr(app.img.handle, &app.img.bpp,
			&app.img.line_len, &app.img.endian);

	mlx_hook(app.win, DestroyNotify, StructureNotifyMask, app_destroy, &app);
	mlx_hook(app.win, KeyPress, KeyPressMask, on_keypress, &app);
	mlx_loop_hook(app.mlx, on_frame, &app);
	mlx_loop(app.mlx);
	return (0);
}
