/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:22:16 by lpaquatt          #+#    #+#             */
/*   Updated: 2024/01/08 19:58:44 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

int	player_on_ground(t_var *vars)
{
	int	x;
	int	y;
	char	tile_bellow;

	x = vars->game->player->position->x_tile;
	y = vars->game->player->position->y_tile;
	tile_bellow = vars->map->tiles[y + 1][x];
	if (tile_bellow == 'C' || tile_bellow == '0')
		return (FALSE);
	return (TRUE);
}

void	animate_normal(t_var *vars, t_anim *player)
{
	if (player->position->pos_on_tile == POS_UP)
		player->position->pos_on_tile = POS_CENTER;
	else if (player_on_ground(vars) == FALSE)
	{
		move_player(vars, 0, 1);
		player->position->pos_on_tile = POS_UP;
		player->movement = FALL;
		player->anim_frame = 0;
	}
	else
		player->anim_frame += 2 * ((player->anim_frame + 1) % 2) - 1;
}

void	animate_jump(t_var *vars, t_anim *player)
{
	player->anim_frame += 1;
	if (player->anim_frame == 2
		&& vars->map->tiles[player->position->y_tile -1][player->position->x_tile] == '0')
		player->position->pos_on_tile = POS_UP;
	else if (player->anim_frame == 3
		&& vars->map->tiles[player->position->y_tile -1][player->position->x_tile] == '0')
	{
		player->position->pos_on_tile = POS_CENTER;
		move_on_tiles(vars, 0, -1);
	}
	else if (player->anim_frame == 4)
	{
		player->movement = FALL;
		player->anim_frame = 0;
	}
}

void	animate_walk(t_var *vars, t_anim *player)
{
	(void) vars;
	
	player->anim_frame += 1;
	if (player->anim_frame == 1)
	{
		player->position->pos_on_tile = POS_LEFT;
		move_on_tiles(vars, 1, 0);
	}
	else if (player->anim_frame == 2)
		player->position->pos_on_tile = POS_CENTER;
	else if (player->anim_frame == 3)
	{
		player->movement = NORMAL;
		player->anim_frame = 0;
		if (player_on_ground(vars) == FALSE)
			animate_fall(vars, player);
		animate_normal(vars, player);
	}
	else if (player->anim_frame == 5)
	{
		player->position->pos_on_tile = POS_RIGHT;
		move_on_tiles(vars, -1, 0);
	}
	else if (player->anim_frame == 6)
		player->position->pos_on_tile = POS_CENTER;
	else if (player->anim_frame == 7)
	{
		player->movement = NORMAL;
		player->anim_frame = 2;
		if (player_on_ground(vars) == FALSE)
			animate_fall(vars, player);
		animate_normal(vars, player);
	}
}

void	animate_fall(t_var *vars, t_anim *player)
{
	if (player->position->pos_on_tile == POS_UP 
		|| player->position->pos_on_tile == POS_LEFT
		|| player->position->pos_on_tile == POS_RIGHT)
	{
		player->position->pos_on_tile = POS_CENTER;
		player->direction = DIR_DOWN;
	}
	else if (player_on_ground(vars) == FALSE)
	{
		move_player(vars, 0, 1);
		player->position->pos_on_tile = POS_UP;
		player->movement = FALL;
		player->anim_frame = 0;
		player->direction = DIR_DOWN;
	}
	else
	{
		player->anim_frame += 1;
		if (player->anim_frame == 4)
		{
			player->movement = NORMAL;
			if (player->direction == DIR_LEFT)
				player->anim_frame = 2;
			else
				player->anim_frame = 0;
		}
	}
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

void	animate_player(t_var *vars)
{
	struct timeval	te;
	time_t		current_timestamp;

	gettimeofday(&te, NULL); // get current time
    current_timestamp = (time_t) ((te.tv_sec * 1000) + te.tv_usec / 1000);
	if (vars->game->player->timestamp == 0)
		vars->game->player->timestamp = current_timestamp;
	if (vars->game->player->timestamp == -1)
	{
		first_animation (vars, vars->game->player, current_timestamp);
	}
	if (current_timestamp - vars->game->player->timestamp < 150)
		return ;
	if (vars->game->player->movement == WALK)
	{

		animate_walk(vars, vars->game->player);
		vars->game->player->timestamp = current_timestamp;
	}
	if (vars->game->player->movement == JUMP)
	{
		animate_jump(vars, vars->game->player);
		vars->game->player->timestamp = current_timestamp;
	}
		if (vars->game->player->movement == FALL)
	{
		animate_fall(vars, vars->game->player);
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