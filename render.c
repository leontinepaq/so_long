/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 23:19:41 by lpaquatt          #+#    #+#             */
/*   Updated: 2023/12/29 17:59:53 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

int	put_one_tile(int x, int y, t_var *vars, char *path)
{
	t_img	*tile;

	tile = file_to_image(vars, path);
	if (!tile)
		return (EXIT_FAILURE);
	overlap_image(vars, tile, (x * TILE_SIZE) - OVERLAP_SIZE,
		(y * TILE_SIZE) - OVERLAP_SIZE);
	mlx_destroy_image(vars->mlx, tile->img_ptr);
	free(tile);
	return (EXIT_SUCCESS);
}

int	put_specific_tile(int x, int y, t_var *vars)
{
	int	res_exit;

	res_exit = EXIT_SUCCESS;
	if (vars->map->tiles[y][x] == '1'
		&& y > 1 && vars->map->tiles[y - 1][x] != '1')
		res_exit = put_one_tile(x, y, vars, "designs/tile_walk_in.xpm");
	else if (vars->map->tiles[y][x] == '1')
		res_exit = put_one_tile(x, y, vars, "designs/tile_wall.xpm");
	else if (vars->map->tiles[y][x] == 'C')
		res_exit = put_one_tile(x, y, vars, "designs/champ_final.xpm");
	else if (vars->map->tiles[y][x] == 'E')
		res_exit = put_one_tile(x, y, vars, "designs/exit_close6.xpm");
	else if (vars->map->tiles[y][x] == 'e')
		res_exit = put_one_tile(x, y, vars, "designs/exit_open6.xpm");
	return (res_exit);
}

int	put_tiles(t_var *vars)
{
	int	x;
	int	y;
	int	x_exit;
	int	y_exit;

	y = 0;
	while (y < vars->map->height)
	{
		x = 0;
		while (x < vars->map->width)
		{
			if (vars->map->tiles[y][x] == 'E' || vars->map->tiles[y][x] == 'e')
			{
				x_exit = x;
				y_exit = y;
			}
			if (put_specific_tile(x, y, vars) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			x++;
		}
		y++;
	}
	if (put_specific_tile(x_exit, y_exit, vars) == EXIT_FAILURE)
		return (EXIT_FAILURE);
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
	if (put_player(vars) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img_ptr, 0, 0);
	mlx_destroy_image(vars->mlx, vars->img->img_ptr);
	free(vars->img);
	return (EXIT_SUCCESS);
}
