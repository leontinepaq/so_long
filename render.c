/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 23:19:41 by lpaquatt          #+#    #+#             */
/*   Updated: 2024/01/08 23:20:53 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

void	put_specific_tile(int x, int y, t_var *vars)
{
	if (vars->map->tiles[y][x] == '1'
		&& y > 1 && vars->map->tiles[y - 1][x] != '1')
		overlap_image(vars, vars->assets->tile_ground,
			((x * TILE_SIZE) - OVERLAP_SIZE) * vars->scale,
			((y * TILE_SIZE) - OVERLAP_SIZE) * vars->scale);
	else if (vars->map->tiles[y][x] == '1')
		overlap_image(vars, vars->assets->tile_wall,
			((x * TILE_SIZE) - OVERLAP_SIZE) * vars->scale,
			((y * TILE_SIZE) - OVERLAP_SIZE) * vars->scale);
	else if (vars->map->tiles[y][x] == 'C')
		overlap_image(vars, vars->assets->collectible,
			((x * TILE_SIZE) - OVERLAP_SIZE) * vars->scale,
			((y * TILE_SIZE) - OVERLAP_SIZE) * vars->scale);
	else if (vars->map->tiles[y][x] == 'E')
		overlap_image(vars, vars->assets->exit_close,
			((x * TILE_SIZE) - OVERLAP_SIZE) * vars->scale,
			((y * TILE_SIZE) - OVERLAP_SIZE) * vars->scale);
	else if (vars->map->tiles[y][x] == 'e')
		overlap_image(vars, vars->assets->exit_open,
			((x * TILE_SIZE) - OVERLAP_SIZE) * vars->scale,
			((y * TILE_SIZE) - OVERLAP_SIZE) * vars->scale);
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
			put_specific_tile(x, y, vars);
			x++;
		}
		y++;
	}
	put_specific_tile(x_exit, y_exit, vars);
	return (EXIT_SUCCESS);
}

int	render(t_var *vars)
{
	if (!vars->win)
		return (EXIT_FAILURE);
	animate_player(vars);
	if (put_background(vars) == EXIT_FAILURE
		|| put_tiles(vars) == EXIT_FAILURE
		|| put_player(vars) == EXIT_FAILURE)
		return (close_window(vars), EXIT_FAILURE);
	if (vars->game->end_of_game == 1)
	{
		overlap_image(vars, vars->assets->victory,
			(vars->game->player->position->x_tile - 1)
			* TILE_SIZE * vars->scale,
			(vars->game->player->position->y_tile - 1)
			* TILE_SIZE * vars->scale);
	}
	if (mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img_ptr, 0, 0)
		== EXIT_FAILURE)
		return (ft_printf(ERROR_MLX), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
