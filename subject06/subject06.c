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
	/* TODO: brush_size, brush_color, painting flag, bg color */
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

Meta: mini-projeto (paint) com mouse + salvar PPM.

Este starter compila e abre a janela; o resto é para você implementar.
*/

static int	on_keypress(int keysym, t_app *app)
{
	/* TODO: ESC fecha */
	/* TODO: S salva output.ppm */
	if (keysym == XK_Escape)
		app_destroy(app);
	return (0);
}

static int	on_mousedown(int button, int x, int y, t_app *app)
{
	/* TODO: clique esquerdo pinta */
	/* TODO: clique direito limpa */
	/* TODO: scroll muda brush */
	(void)button;
	(void)x;
	(void)y;
	(void)app;
	return (0);
}

static int	on_frame(t_app *app)
{
	/* TODO: put_image + HUD */
	(void)app;
	return (0);
}

int	main(void)
{
	t_app app;

	app.width = 900;
	app.height = 600;
	app.mlx = mlx_init();
	if (!app.mlx)
		return (1);
	app.win = mlx_new_window(app.mlx, app.width, app.height,
			"subject06 - starter");
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
