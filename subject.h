/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subject.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilly <smilly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 11:22:37 by smilly            #+#    #+#             */
/*   Updated: 2026/01/26 16:32:00 by smilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_data
{
	void	*mlx;			// contexto MLX (mlx_init)
	void	*win;			// janela (mlx_new_window)

	void	*img;			// imagem off-screen (mlx_new_image)
	char	*addr;			// endereço do buffer de pixels
	int		bits_per_pixel;	// bits por pixel (ex: 32)
	int		line_length;	// bytes por linha
	int		endian;			// ordem dos bytes

	int		w;				// largura
	int		h;				// altura

	    // Estado do "jogo"/animação
    int     rx;     // rect x
    int     ry;     // rect y
    int     rw;     // rect width
    int     rh;     // rect height
    int     vx;     // velocity x
    int     vy;     // velocity y

	// double zoom;
    // double offset_x;
    // double offset_y;
    // int    max_iter;
}	t_data;