/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 11:28:58 by nasargsy          #+#    #+#             */
/*   Updated: 2025/04/14 14:42:44 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

static int	check_julia_input(char *argv)
{
	int	i;

	i = 0;
	if (argv[i] == '-' || argv[i] == '+')
		++i;
	while (argv[i] != '.' && argv[i])
	{
		if (!ft_isdigit(argv[i]))
			quit_with_error(ERROR_MSG);
		++i;
	}
	if (!argv[i] && ft_atod(argv) <= 2.0 && ft_atod(argv) >= -2.0)
		return (1);
	++i;
	while (argv[i] && !ft_isspace(argv[i]))
	{
		if (!ft_isdigit(argv[i]))
			quit_with_error(ERROR_MSG);
		++i;
	}
	while (ft_isspace(argv[i]) && argv[i])
		i++;
	if (argv[i] || ft_atod(argv) > 2.0 || ft_atod(argv) <= -2.0)
		quit_with_error(ERROR_MSG);
	return (1);
}

static int	check_mandelbrot(char *argv)
{
	int	i;

	i = 10;
	while (ft_isspace(argv[i]) && argv[i])
		++i;
	if (argv[i])
		quit_with_error(ERROR_MSG);
	return (1);
}

static void	check_input(int argc, char **argv)
{
	if (argc == 1 || argc > 4)
		quit_with_error(ERROR_MSG);
	while (ft_isspace(*(argv[1])))
		++argv[1];
	if ((ft_strncmp(argv[1], "mandelbrot", 10) == 0
			&& argc == 2)
		|| ((ft_strncmp(argv[1], "julia", 5) == 0)
			&& argc == 4))
	{
		if (ft_strncmp(argv[1], "mandelbrot", 10) == 0)
			check_mandelbrot(argv[1]);
		if (ft_strncmp(argv[1], "julia", 5) == 0)
		{
			while (ft_isspace(*(argv[2])))
				++argv[2];
			check_julia_input(argv[2]);
			while (ft_isspace(*(argv[3])))
				++argv[3];
			check_julia_input(argv[3]);
		}
	}
	else
		quit_with_error(ERROR_MSG);
}

static void	fractal_init(t_fractal	*fractal)
{
	fractal->mlx_ptr = mlx_init();
	if (fractal->mlx_ptr == NULL)
		quit_with_error("mlx_init()\n");
	fractal->mlx_win = mlx_new_window(fractal->mlx_ptr,
			800,
			800,
			fractal->name);
	if (fractal->mlx_win == NULL)
	{
		clean_fractal(fractal);
		quit_with_error("mlx_new_window()\n");
	}
	fractal->img.img_ptr = mlx_new_image(fractal->mlx_ptr, 800, 800);
	if (fractal->img.img_ptr == NULL)
	{
		clean_fractal(fractal);
		quit_with_error("mlx_new_image()\n");
	}
	fractal->img.pixels_ptr = mlx_get_data_addr(fractal->img.img_ptr,
			&fractal->img.bpp,
			&fractal->img.length,
			&fractal->img.endian);
}

int	main(int argc, char **argv)
{
	t_fractal	fractal;

	check_input(argc, argv);
	fractal.name = argv[1];
	fractal.size = 50;
	fractal.shift_x = 0.0;
	fractal.shift_y = 0.0;
	fractal.zoom = 1.0;
	if (ft_strncmp(fractal.name, "julia", 5) == 0)
	{
		fractal.julia_x = ft_atod(argv[2]);
		fractal.julia_y = ft_atod(argv[3]);
	}
	fractal_init(&fractal);
	fractal_render(&fractal);
	event_handler(&fractal);
	mlx_loop(fractal.mlx_ptr);
}
