/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closing_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 19:18:02 by lpaquatt          #+#    #+#             */
/*   Updated: 2023/12/22 19:19:52 by lpaquatt         ###   ########.fr       */
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

void	free_map(t_map *map)
{
	if (!map)
		return ;
	if (map->content)
		free(map->content);
	if (map->tiles)
		free_tiles(map);
	free(map);
}

int	escape(int keysym, t_var *vars)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		vars->win = NULL;
	}
	return (EXIT_SUCCESS);
}

int	close_window(t_var *vars)
{
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
	{
		mlx_destroy_display(vars->mlx);
		free (vars->mlx);
	}
	return (EXIT_SUCCESS);
}

int	closure(t_var *vars)
{
	close_window(vars);
	free_map(vars->map);
	free(vars);
	exit(0);
	return (EXIT_SUCCESS);
}
