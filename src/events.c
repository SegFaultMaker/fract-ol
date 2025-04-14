/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:14:22 by nasargsy          #+#    #+#             */
/*   Updated: 2025/04/10 13:14:31 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

static int	close_handle(t_fractal *fractal)
{
	clean_fractal(fractal);
	exit(1);
}

static int	mouse_handle(int button, int x, int y, t_fractal *fractal)
{
	if (button == Button5)
		fractal->zoom *= 1.05;
	else if (button == Button4)
		fractal->zoom *= 0.95;
	fractal->shift_x += (x - 400) * fractal->zoom / 400.0;
	fractal->shift_y += (y - 400) * fractal->zoom / 400.0;
	mlx_destroy_image(fractal->mlx_ptr, fractal->img.img_ptr);
	fractal->img.img_ptr = mlx_new_image(fractal->mlx_ptr, 800, 800);
	fractal_render(fractal);
	return (0);
}

static int	key_handle(int keysym, t_fractal *fractal)
{
	if (keysym == XK_Escape)
	{
		clean_fractal(fractal);
		exit (1);
	}
	if (keysym == XK_Left)
		fractal->shift_x += (0.5 * fractal->zoom);
	else if (keysym == XK_Right)
		fractal->shift_x -= (0.5 * fractal->zoom);
	else if (keysym == XK_Up)
		fractal->shift_y -= (0.5 * fractal->zoom);
	else if (keysym == XK_Down)
		fractal->shift_y += (0.5 * fractal->zoom);
	else if (keysym == XK_equal)
		fractal->size += 10;
	else if (keysym == XK_minus)
		fractal->size -= 10;
	mlx_destroy_image(fractal->mlx_ptr, fractal->img.img_ptr);
	fractal->img.img_ptr = mlx_new_image(fractal->mlx_ptr, 800, 800);
	fractal_render(fractal);
	return (0);
}

void	event_handler(t_fractal *fractal)
{
	mlx_hook(fractal->mlx_win,
		KeyPress, KeyPressMask,
		key_handle, fractal);
	mlx_hook(fractal->mlx_win,
		ButtonPress, ButtonPressMask,
		mouse_handle, fractal);
	mlx_hook(fractal->mlx_win,
		DestroyNotify, StructureNotifyMask,
		close_handle, fractal);
}
