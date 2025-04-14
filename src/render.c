/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:35:27 by nasargsy          #+#    #+#             */
/*   Updated: 2025/04/08 14:50:17 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

static double	scale(double orig_num, double old_min, double old_max)
{
	return ((2 - (-2)) * (orig_num - old_min) / (old_max - old_min) + (-2));
}

static double	get_color(double orig_num, double old_min, double old_max)
{
	return ((BLACK - WHITE) * (orig_num - old_min) / (old_max - old_min));
}

static void	set_c(t_complex *z, t_complex *c, t_fractal *fractal)
{
	if (ft_strncmp(fractal->name, "mandelbrot", 10) == 0)
	{
		c->x = z->x;
		c->y = z->y;
		z->x = 0.0;
		z->y = 0.0;
	}
	else
	{
		c->x = fractal->julia_x;
		c->y = fractal->julia_y;
	}
}

static void	handle_pixel(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;
	double		magnitude;

	i = -1;
	z.x = (scale(x, 0, 799) * fractal->zoom) + fractal->shift_x;
	z.y = (scale(y, 0, 799) * fractal->zoom) + fractal->shift_y;
	set_c(&z, &c, fractal);
	magnitude = 0.0;
	while (++i < fractal->size)
	{
		z = sum_complex(square_complex(z), c);
		magnitude = z.x * z.x + z.y * z.y;
		if (magnitude > 4.0)
			break ;
	}
	if (magnitude > 4.0)
	{
		color = get_color(i, 0, fractal->size);
		if (color != 0)
			my_mlx_pixel_put(&fractal->img, x, y, color);
	}
}

void	fractal_render(t_fractal *fractal)
{
	int	x;
	int	y;

	y = -1;
	while (++y < 800)
	{
		x = -1;
		while (++x < 800)
		{
			handle_pixel(x, y, fractal);
		}
	}
	mlx_put_image_to_window(fractal->mlx_ptr, fractal->mlx_win,
		fractal->img.img_ptr, 0, 0);
}
