/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_linux.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilly <smilly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 17:08:21 by smilly            #+#    #+#             */
/*   Updated: 2026/01/30 17:08:37 by smilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_LINUX_H
# define MLX_LINUX_H

/*
** This header is a compatibility layer for Linux, similar to mlx_macos.h.
** It defines common X11 event IDs, masks, and keycodes to provide a
** consistent interface across platforms for project source code.
*/

// Include the official MiniLibX header for Linux.
# include "minilibx-linux/mlx.h"

/* X11-like event ids */
# define KeyPress 2
# define KeyRelease 3
# define ButtonPress 4
# define ButtonRelease 5
# define MotionNotify 6
# define Expose 12
# define DestroyNotify 17

/* Masks */
# define KeyPressMask (1L<<0)
# define KeyReleaseMask (1L<<1)
# define ButtonPressMask (1L<<2)
# define ButtonReleaseMask (1L<<3)
# define PointerMotionMask (1L<<6)
# define ExposureMask (1L<<15)
# define StructureNotifyMask (1L<<17)

/* Common keycodes (X11 Keysyms) */
# define XK_Escape 65307
# define XK_space 32

# define XK_Left 65361
# define XK_Right 65363
# define XK_Down 65364
# define XK_Up 65362

/* Letters on a US QWERTY layout */
# define XK_a 97
# define XK_s 115
# define XK_d 100
# define XK_w 119
# define XK_p 112

#endif
