/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_movements.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 20:20:53 by lpaquatt          #+#    #+#             */
/*   Updated: 2024/01/19 11:45:14 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

void	animate_normal(t_var *vars, t_anim *player)
{
	if (player->position->pos_on_tile == POS_UP)
		player->position->pos_on_tile = POS_CENTER;
	else if (is_player_on_ground(vars) == FALSE)
	{
		move_on_tiles(vars, 0, 1);
		player->position->pos_on_tile = POS_UP;
		player->movement = FALL;
		player->anim_frame = 0;
	}
	else
		player->anim_frame += 2 * ((player->anim_frame + 1) % 2) - 1;
}

void	animate_walk_left(t_var *vars, t_anim *player)
{
	player->anim_frame += 1;
	if (player->anim_frame == 5)
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
		if (is_player_on_ground(vars) == FALSE)
			animate_fall(vars, player);
		animate_normal(vars, player);
	}
}

void	animate_walk_right(t_var *vars, t_anim *player)
{
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
		if (is_player_on_ground(vars) == FALSE)
			animate_fall(vars, player);
		animate_normal(vars, player);
	}
}

void	animate_jump(t_var *vars, t_anim *player)
{
	int	x;
	int	y;

	x = player->position->x_tile;
	y = player->position->y_tile;
	if (player->anim_frame == 0 && player->direction != DIR_UP)
	{
		player->movement = FALL;
		return ;
	}
	player->anim_frame += 1;
	if (player->anim_frame == 2
		&& vars->map->tiles[y - 1][x] == '0')
		player->position->pos_on_tile = POS_UP;
	else if (player->anim_frame == 3
		&& vars->map->tiles[y - 1][x] == '0')
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

void	animate_fall(t_var *vars, t_anim *player)
{
	if (player->position->pos_on_tile == POS_UP
		|| player->position->pos_on_tile == POS_LEFT
		|| player->position->pos_on_tile == POS_RIGHT)
		player->position->pos_on_tile = POS_CENTER;
	else if (is_player_on_ground(vars) == FALSE)
	{
		move_on_tiles(vars, 0, 1);
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
