/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subject.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilly <smilly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 16:26:01 by smilly            #+#    #+#             */
/*   Updated: 2026/01/30 20:02:01 by smilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUBJECT_H
# define SUBJECT_H

# include <unistd.h>
# include <stdlib.h> 
# include <stdio.h>
# include "minilibx-linux/mlx.h"
// # include "mlx_macos.h"
# include "keys.h"

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		w;
	int		h;

	double	zoom;
	double	shift_x;
	double	shift_y;
	int		max_iter;

	double	julia_re;
	double	julia_im;

	int		dirty;			// flag: precisa redesenhar
	double	color_shift;	// deslocamento para mudar as cores
}			t_data;

#endif
