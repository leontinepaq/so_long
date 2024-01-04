/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:47:15 by lpaquatt          #+#    #+#             */
/*   Updated: 2024/01/03 16:19:12 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

void	free_tiles(t_map *map)
{
	int	y;

	if (!map->tiles)
		return ;
	y = 0;
	while (y < map->height && map->tiles[y])
	{
		free(map->tiles[y]);
		y++;
	}
	free(map->tiles);
}

void	free_one_asset(void *mlx, t_img *asset)
{
	if (!asset)
		return ;
	mlx_destroy_image(mlx, asset->img_ptr);
	free(asset);
}

void	free_assets(t_var *vars)
{
	free_one_asset(vars->mlx, vars->assets->collectible);
	free_one_asset(vars->mlx, vars->assets->exit_close);
	free_one_asset(vars->mlx, vars->assets->exit_open);
	free_one_asset(vars->mlx, vars->assets->player);
	free_one_asset(vars->mlx, vars->assets->tile_ground);
	free_one_asset(vars->mlx, vars->assets->tile_wall);
	free_one_asset(vars->mlx, vars->assets->background_1);
	free_one_asset(vars->mlx, vars->assets->background_2);
	free_one_asset(vars->mlx, vars->assets->background_3);
	free(vars->assets);
}

void	free_vars(t_var *vars)
{
	if (vars->map)
	{
		if (vars->map->content)
			free(vars->map->content);
		if (vars->map->tiles)
			free_tiles(vars->map);
		free(vars->map);
	}
	if (vars->game)
	{
		if (vars->game->pos_player)
			free(vars->game->pos_player);
		free (vars->game);
	}
	if (vars->img)
	{
		free(vars->img);
	}
	if (vars)
		free(vars);
}