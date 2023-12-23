/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 23:19:41 by lpaquatt          #+#    #+#             */
/*   Updated: 2023/12/23 01:03:42 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

int	put_layer_background(t_var *vars, char *path)
{
	t_img	*background;
	int		i;
	int		j;

	i = 0;
	background = file_to_image(vars, path);
	if (!background)
		return (EXIT_FAILURE);
	while (i * background->width < vars->img->width)
	{
		j = 0;
		while (j * background->height < vars->img->height)
		{
			overlap_image(vars, background, i * background->width,
				j * background->height);
			j++;
		}
		i++;
	}
	mlx_destroy_image(vars->mlx, background->img_ptr);
	free(background);
	return (EXIT_SUCCESS);
}

int	put_background(t_var *vars)
{
	if (put_layer_background(vars, "designs/Rock1.xpm") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (put_layer_background(vars, "designs/Rock2.xpm") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (put_layer_background(vars, "designs/Rock3.xpm") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	put_one_tile(int x, int y, t_var *vars, char *path)
{
	t_img	*tile;

	tile = file_to_image(vars, path);
	if (!tile)
		return (EXIT_FAILURE);
	overlap_image(vars, tile, (x * TILE_SIZE) - OVERLAP_SIZE, (y * TILE_SIZE) - OVERLAP_SIZE);
	mlx_destroy_image(vars->mlx, tile->img_ptr);
	free(tile);
	return (EXIT_SUCCESS);
}


int	put_tiles(t_var *vars)
{
	int	x;
	int	y;
	
	y = 0;
	while (y < vars->map->height)
	{
		x = 0;
		while (x < vars->map->width)
		{
			if (vars->map->tiles[y][x] == '1' && y > 1 && vars->map->tiles[y - 1][x] != '1')
			{
				if (put_one_tile(x, y, vars, "designs/tile_walk_in.xpm") == EXIT_FAILURE)
					return (EXIT_FAILURE);
			}
			else if (vars->map->tiles[y][x] == '1')
			{
				if (put_one_tile(x, y, vars, "designs/tile_wall.xpm") == EXIT_FAILURE)
					return (EXIT_FAILURE);
			}
			x++;
		}
		y++;
	}
	return (EXIT_SUCCESS);	
}

int	render(t_var *vars)
{
	if (!vars->win)
		return (EXIT_FAILURE);
	vars->img = malloc(sizeof(t_img));
	if (!vars->img)
		return (ft_printf(ERROR_MALLOC), EXIT_FAILURE);
// check si malloc -> fermer window ?
	vars->img->width = vars->map->width * TILE_SIZE;
	vars->img->height = vars->map->height * TILE_SIZE;
	vars->img->img_ptr = mlx_new_image(vars->mlx,
			vars->img->width, vars->img->height);
	if (!vars->img->img_ptr)
		return (ft_printf(ERROR_MLX), EXIT_FAILURE);
	vars->img->img_pixels_ptr = mlx_get_data_addr(vars->img->img_ptr,
			&vars->img->bits_per_pixel,
			&vars->img->line_len, &vars->img->endian);
	if (put_background(vars) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (put_tiles(vars) == EXIT_FAILURE)
		return (EXIT_FAILURE);	
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img_ptr, 0, 0);
	mlx_destroy_image(vars->mlx, vars->img->img_ptr);
	free(vars->img);
	return (EXIT_SUCCESS);
}
