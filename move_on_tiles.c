/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_on_tiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 22:13:35 by lpaquatt          #+#    #+#             */
/*   Updated: 2024/01/18 22:17:00 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

void	collect_collectibles(t_var *vars)
{
	vars->game->collectibles--;
	if (vars->game->collectibles == 0)
		open_exit(vars);
}

void	move_on_tiles(t_var *vars, int move_x, int move_y)
{
	int	x;
	int	y;

	if (vars->game->end_of_game == 1 || vars->game->end_of_game == -1)
		return ;
	x = vars->game->player->position->x_tile;
	y = vars->game->player->position->y_tile;
	if (vars->map->tiles[y + move_y][x + move_x] == '1'
		|| vars->map->tiles[y + move_y][x + move_x] == 'E')
		return ;
	if (vars->map->tiles[y + move_y][x + move_x] == 'C')
		collect_collectibles(vars);
	if (vars->map->tiles[y + move_y][x + move_x] != 'e'
		&& vars->map->tiles[y + move_y][x + move_x] != 'M')
		vars->map->tiles[y + move_y][x + move_x] = 'P';
	else if (vars->map->tiles[y + move_y][x + move_x] == 'M')
		vars->map->tiles[y + move_y][x + move_x] = 'm';
	if (vars->map->tiles[y][x] == 'm')
		vars->map->tiles[y][x] = 'M';
	else
		vars->map->tiles[y][x] = '0';
	vars->game->player->position->x_tile += move_x;
	vars->game->player->position->y_tile += move_y;
}
