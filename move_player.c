/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 20:03:57 by lpaquatt          #+#    #+#             */
/*   Updated: 2024/01/08 20:18:49 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

void	update_player_on_x(t_var *vars, int move_x)
{
	int	x;
	int	y;

	x = vars->game->player->position->x_tile;
	y = vars->game->player->position->y_tile;
	if (move_x == -1)
	{
		vars->game->player->direction = DIR_LEFT;
		if (vars->map->tiles[y + 1][x] == '1')
		{
			vars->game->player->movement = WALK;
			vars->game->player->anim_frame = 4;
			vars->game->player->timestamp = -1;
		}
	}
	else if (move_x == 1)
	{
		vars->game->player->direction = DIR_RIGHT;
		if (vars->map->tiles[y + 1][x] == '1')
		{
			vars->game->player->movement = WALK;
			vars->game->player->anim_frame = 0;
			vars->game->player->timestamp = -1;
		}
	}
}

void	update_player_on_y(t_var *vars, int move_y)
{
	if (move_y == -1)
	{
		vars->game->player->movement = JUMP;
		vars->game->player->direction = DIR_UP;
		vars->game->player->anim_frame = 0;
		vars->game->player->timestamp = -1;
	}
	else if (move_y == 1)
	{
		vars->game->player->movement = FALL;
		vars->game->player->direction = DIR_DOWN;
		vars->game->player->anim_frame = 0;
	}
}

void	move_on_tiles(t_var *vars, int move_x, int move_y)
{
	int	x;
	int	y;

	if (vars->game->end_of_game == 1)
		return ;
	x = vars->game->player->position->x_tile;
	y = vars->game->player->position->y_tile;
	if (vars->map->tiles[y + move_y][x + move_x] == '1'
		|| vars->map->tiles[y + move_y][x + move_x] == 'E')
		return ;
	if (vars->map->tiles[y + move_y][x + move_x] == 'C')
	{
		vars->game->collectibles--;
		if (vars->game->collectibles == 0)
			open_exit(vars);
	}
	if (vars->map->tiles[y + move_y][x + move_x] != 'e')
		vars->map->tiles[y + move_y][x + move_x] = 'P';
	vars->map->tiles[y][x] = '0';
	vars->game->player->position->x_tile += move_x;
	vars->game->player->position->y_tile += move_y;
}

void	move_player(t_var *vars, int move_x, int move_y)
{
	int	x;
	int	y;

	x = vars->game->player->position->x_tile;
	y = vars->game->player->position->y_tile;
	if (vars->game->end_of_game == 1)
		return ;
	if (vars->map->tiles[y + move_y][x + move_x] == 'C'
		|| vars->map->tiles[y + move_y][x + move_x] == '0')
	{
		move_on_tiles(vars, move_x, move_y);
		if (move_x != 0)
			update_player_on_x(vars, move_x);
		if (move_y != 0)
			update_player_on_y(vars, move_y);
		vars->game->moves++;
	}
	else if (vars->map->tiles[y + move_y][x + move_x] == 'e')
		display_victory(vars, move_x, move_y);
}
