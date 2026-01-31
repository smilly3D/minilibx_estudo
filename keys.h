/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilly <smilly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:42:00 by smilly            #+#    #+#             */
/*   Updated: 2026/01/30 18:48:19 by smilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

/*
** Fract-ol (MiniLibX) key/button codes differ between:
** - macOS mlx (Quartz)
** - Linux mlx (X11)
**
** Use these enums to keep the rest of the code portable.
*/

# ifdef __linux__

/* ---------- X11 EVENTS (Linux) ---------- */
enum e_x11_event
{
	KEY_PRESS		= 2,
	KEY_RELEASE		= 3,
	BUTTON_PRESS	= 4,
	BUTTON_RELEASE	= 5,
	MOTION_NOTIFY	= 6,
	DESTROY_NOTIFY	= 17
};

/* ---------- X11 KEYS (Linux) ---------- */
enum e_keys
{
	KEY_ESC		= 65307,

	KEY_LEFT	= 65361,
	KEY_UP		= 65362,
	KEY_RIGHT	= 65363,
	KEY_DOWN	= 65364,

	KEY_W		= 119,
	KEY_A		= 97,
	KEY_S		= 115,
	KEY_D		= 100,

	KEY_R		= 114, /* reset */
	KEY_C		= 99, /* toggle color / palette */
	KEY_J		= 106, /* julia mode (optional) */
	KEY_1		= 49,
	KEY_2		= 50,
	KEY_3		= 51
};

/* ---------- X11 MOUSE BUTTONS (Linux) ---------- */
enum e_mouse
{
	MOUSE_LEFT		= 1,
	MOUSE_MIDDLE	= 2,
	MOUSE_RIGHT		= 3,
	SCROLL_UP		= 4, /* zoom in */
	SCROLL_DOWN		= 5 /* zoom out */
};

# else

/* ---------- macOS EVENTS (mlx mac) ---------- */
enum e_macos_event
{
	KEY_PRESS		= 2,
	KEY_RELEASE		= 3,
	BUTTON_PRESS	= 4,
	BUTTON_RELEASE	= 5,
	MOTION_NOTIFY	= 6,
	DESTROY_NOTIFY	= 17
};

/* ---------- macOS KEYS ---------- */
enum e_keys
{
	KEY_ESC		= 53,

	KEY_LEFT	= 123,
	KEY_RIGHT	= 124,
	KEY_DOWN	= 125,
	KEY_UP		= 126,

	KEY_W		= 13,
	KEY_A		= 0,
	KEY_S		= 1,
	KEY_D		= 2,

	KEY_R		= 15, /* reset */
	KEY_C		= 8, /* toggle color / palette */
	KEY_J		= 38, /* julia mode (optional) */
	KEY_1		= 18,
	KEY_2		= 19,
	KEY_3		= 20
};

/* ---------- macOS MOUSE BUTTONS ---------- */
enum e_mouse
{
	MOUSE_LEFT		= 1,
	MOUSE_RIGHT		= 2,
	MOUSE_MIDDLE	= 3,
	SCROLL_UP		= 4, /* zoom in (em muitas mlx mac) */
	SCROLL_DOWN		= 5 /* zoom out */
};

# endif

#endif
