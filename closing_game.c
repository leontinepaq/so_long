/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closing_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 19:18:02 by lpaquatt          #+#    #+#             */
/*   Updated: 2023/12/29 21:56:37 by lpaquatt         ###   ########.fr       */
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
		free (vars->game);
	if (vars)
		free(vars);
}

void	close_window(t_var *vars)
{
	if (vars->win)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		vars->win = NULL;
	}

}

int	closure(t_var *vars)
{
	close_window(vars);
	if (vars->mlx)
	{
		mlx_destroy_display(vars->mlx);
		free (vars->mlx);
		vars->mlx = NULL;
	}
	free_vars(vars);
	exit(0);
	return (EXIT_SUCCESS);
}
