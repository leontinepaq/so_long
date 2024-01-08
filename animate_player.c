/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:22:16 by lpaquatt          #+#    #+#             */
/*   Updated: 2024/01/08 21:03:21 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

int	is_player_on_ground(t_var *vars)
{
	int		x;
	int		y;
	char	tile_bellow;

	x = vars->game->player->position->x_tile;
	y = vars->game->player->position->y_tile;
	tile_bellow = vars->map->tiles[y + 1][x];
	if (tile_bellow == 'C' || tile_bellow == '0')
		return (FALSE);
	return (TRUE);
}

void	first_animation(t_var *vars, t_anim *player, time_t current_timestamp)
{
	if (player->direction == DIR_LEFT)
	{
		move_on_tiles(vars, 1, 0);
		player->position->pos_on_tile = POS_LEFT;
	}
	if (player->direction == DIR_RIGHT)
	{
		move_on_tiles(vars, -1, 0);
		player->position->pos_on_tile = POS_RIGHT;
	}
	if (player->direction == DIR_UP)
	{
		move_on_tiles(vars, 0, 1);
	}
	player->timestamp = current_timestamp + 1;
}

void	play_movement_animation(t_var *vars)
{
	if (vars->game->player->movement == WALK)
	{
		if (vars->game->player->direction == DIR_LEFT)
			animate_walk_left(vars, vars->game->player);
		if (vars->game->player->direction == DIR_RIGHT)
			animate_walk_right(vars, vars->game->player);
	}
	if (vars->game->player->movement == JUMP)
		animate_jump(vars, vars->game->player);
	if (vars->game->player->movement == FALL)
		animate_fall(vars, vars->game->player);
}

void	animate_player(t_var *vars)
{
	struct timeval	te;
	time_t			current_timestamp;

	gettimeofday(&te, NULL);
	current_timestamp = (time_t)((te.tv_sec * 1000) + te.tv_usec / 1000);
	if (vars->game->player->timestamp == 0)
		vars->game->player->timestamp = current_timestamp;
	if (vars->game->player->timestamp == -1)
		first_animation (vars, vars->game->player, current_timestamp);
	if (current_timestamp - vars->game->player->timestamp < 150)
		return ;
	if (vars->game->player->movement != NORMAL)
	{
		play_movement_animation(vars);
		vars->game->player->timestamp = current_timestamp;
	}
	if (current_timestamp - vars->game->player->timestamp < 700)
		return ;
	if (vars->game->player->movement == NORMAL)
	{
		animate_normal(vars, vars->game->player);
		vars->game->player->timestamp = current_timestamp;
	}
}
/*
		ft_printf("NEXT MOVE\n");
		ft_printf("movement : %d - dir : %d - anim_frame : %d ", vars->game->player->movement, vars->game->player->direction, vars->game->player->anim_frame);
		ft_printf("- pos tile : %d - x_tile : %d\n", vars->game->player->position->pos_on_tile,  vars->game->player->position->x_tile);
*/