/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 12:04:26 by nasargsy          #+#    #+#             */
/*   Updated: 2025/04/07 15:24:08 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	quit_with_error(char *error)
{
	ft_putstr_fd(error, 2);
	exit(1);
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;
	int		offset;

	offset = (y * data->length + x * (data->bpp / 8));
	dst = data->pixels_ptr + offset;
	*(unsigned int *) dst = color;
}

void	clean_fractal(t_fractal	*fractal)
{
	if (fractal->img.img_ptr)
		mlx_destroy_image(fractal->mlx_ptr, fractal->img.img_ptr);
	if (fractal->mlx_win)
		mlx_destroy_window(fractal->mlx_ptr, fractal->mlx_win);
	mlx_destroy_display(fractal->mlx_ptr);
	free(fractal->mlx_ptr);
}

double	ft_atod(const char *s)
{
	long long	integer;
	double		fractional;
	double		pow;
	int			sign;

	integer = 0;
	fractional = 0;
	sign = 1;
	pow = 1;
	while ((*s >= 9 && *s <= 13) || *s == 32)
		s++;
	while (*s == '+' || *s == '-')
		if ('-' == *s++)
			sign *= -1;
	while (ft_isdigit(*s) && *s)
		integer = (integer * 10) + (*s++ - 48);
	if (*s == '.')
		++s;
	while (ft_isdigit(*s))
	{
		pow /= 10;
		fractional = fractional + (*s++ - 48) * pow;
	}
	return ((integer + fractional) * sign);
}
