/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 11:29:04 by nasargsy          #+#    #+#             */
/*   Updated: 2025/04/07 13:51:07 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <unistd.h>
# include <X11/Xlib.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

# define ERROR_MSG "Usage:\n~./fractol mandelbrot\n~./fractol julia <real> <i>\n"
# define MAGENTA      0xFFFF00FF
# define CYAN         0xFF00FFFF
# define ORANGE       0xFFFF8000
# define PURPLE       0xFFFF00FF
# define GREEN        0xFF008000
# define YELLOW       0xFFFFFF00
# define BLUE         0xFF0000FF
# define PINK         0xFFFFC0CB
# define OLIVE        0xFF808000
# define TEAL         0xFF008080
# define VIOLET       0xFFEE82EE
# define LIGHT_PINK   0xFFFFB6C1
# define BLACK        0xFF000000
# define WHITE        0xFFFFFFFF

typedef struct s_complex
{
	double	x;
	double	y;
}	t_complex;

typedef struct s_img
{
	void	*img_ptr;
	char	*pixels_ptr;
	int		bpp;
	int		length;
	int		endian;
}	t_img;

typedef struct s_fractal
{
	char	*name;
	void	*mlx_ptr;
	void	*mlx_win;
	t_img	img;
	int		size;
	double	shift_x;
	double	shift_y;
	double	zoom;
	double	julia_x;
	double	julia_y;
}	t_fractal;

void		quit_with_error(char *error);
void		my_mlx_pixel_put(t_img *data, int x, int y, int color);
void		clean_fractal(t_fractal	*fractal);
void		fractal_render(t_fractal *fractal);
void		event_handler(t_fractal *fractal);
double		ft_atod(const char *str);
t_complex	square_complex(t_complex z1);
t_complex	sum_complex(t_complex z1, t_complex z2);

#endif
