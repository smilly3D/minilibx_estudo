#ifndef MLX_MACOS_H
#define MLX_MACOS_H

/*
** Compatibility header for this repo when using `minilibx_mms` (macOS/Metal).
**
** `minilibx_mms` implements `mlx_hook(win, x_event, x_mask, ...)` using
** X11-like event ids as array indices internally (KeyPress=2, DestroyNotify=17,
** etc). The masks are ignored in this implementation, so we provide them as 0.
**
** Keycodes are macOS virtual keycodes (NSEvent.keyCode).
*/

/* X11-like event ids (used as indices by minilibx_mms) */
#define KeyPress 2
#define KeyRelease 3
#define ButtonPress 4
#define ButtonRelease 5
#define MotionNotify 6
#define Expose 12
#define DestroyNotify 17

/* Masks (ignored by minilibx_mms) */
#define KeyPressMask 0
#define KeyReleaseMask 0
#define ButtonPressMask 0
#define ButtonReleaseMask 0
#define PointerMotionMask 0
#define ExposureMask 0
#define StructureNotifyMask 0

/* Common keycodes (macOS virtual keycodes) */
#define XK_Escape 53
#define XK_space 49

#define XK_Left 123
#define XK_Right 124
#define XK_Down 125
#define XK_Up 126

/* Letters on a US QWERTY layout */
#define XK_a 0
#define XK_s 1
#define XK_d 2
#define XK_w 13
#define XK_p 35

#endif
