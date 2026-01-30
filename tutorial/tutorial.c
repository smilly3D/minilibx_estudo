/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tutorial.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilly <smilly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 20:12:26 by smilly            #+#    #+#             */
/*   Updated: 2026/01/26 12:06:08 by smilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <unistd.h>
#include "../subject.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int i;

	i = 0;
	img.w = 800;
	img.h = 800;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, img.w, img.h, "hellow world!");
	img.img = mlx_new_image(mlx, img.w, img.h);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, 
			&img.line_length, &img.endian);
	while(i < 810)
	{
		my_mlx_pixel_put(&img, i, 5, 0x00FF0000);
		mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
		usleep(1000);
		i++;
	}

	mlx_loop(mlx);

	return (0);
}