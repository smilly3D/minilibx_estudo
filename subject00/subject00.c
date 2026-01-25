/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subject00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilly <smilly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 20:03:05 by smilly            #+#    #+#             */
/*   Updated: 2026/01/24 20:07:19 by smilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

int	main(void)
{
	void	*mlx;
	void	*window;

	mlx = mlx_init();
	if (!mlx)
		return (-1);
	window = mlx_new_window(mlx, 800, 800, "hello world");
	if (!window)
		return (-1);
	mlx_loop(mlx);

	return (0);
}
