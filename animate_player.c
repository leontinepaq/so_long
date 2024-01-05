/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:22:16 by lpaquatt          #+#    #+#             */
/*   Updated: 2024/01/05 17:44:35 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

void	animate_normal(t_var *vars, t_anim *player, t_map *map)
{
	char	tile_bellow;

	tile_bellow = map->tiles[player->position->y_tile + 1][player->position->x_tile];
	if (player->position->pos_on_tile == POS_UP)
		player->position->pos_on_tile = POS_CENTER;
	else if (tile_bellow == '0' || tile_bellow == 'C' )
	{
		move_player(vars, 0, 1);
		player->position->pos_on_tile = POS_UP;
		player->movement = FALL;
		player->anim_frame = 0;
	}
	else
		player->anim_frame += 2 * ((player->anim_frame + 1) % 2) - 1;
}

void	animate_jump(t_var *vars, t_anim *player, t_map *map)
{
	(void) vars;
	(void) map;
	player->anim_frame += 1;
	if (player->anim_frame == 2)
		player->position->pos_on_tile = POS_UP;
	else if (player->anim_frame == 3)
	{
		player->position->pos_on_tile = POS_CENTER;
		player->position->y_tile -= 1;
	}
	else if (player->anim_frame == 4)
	{
		player->movement = FALL;
		player->anim_frame = 0;
	}
}

void	animate_walk(t_var *vars, t_anim *player, t_map *map)
{
	(void) vars;
	(void) map;
	
	player->anim_frame += 1;
	if (player->anim_frame == 1)
	{
		player->position->pos_on_tile = POS_LEFT;
		player->position->x_tile += 1;
	}
	else if (player->anim_frame == 2)
		player->position->pos_on_tile = POS_CENTER;
	else if (player->anim_frame == 3)
	{
		player->movement = NORMAL;
		player->anim_frame = 0;
		animate_normal(vars, player, map);
	}
	else if (player->anim_frame == 5)
	{
		player->position->pos_on_tile = POS_RIGHT;
		player->position->x_tile -= 1;
	}
	else if (player->anim_frame == 6)
		player->position->pos_on_tile = POS_CENTER;
	else if (player->anim_frame == 7)
	{
		player->movement = NORMAL;
		player->anim_frame = 2;
		animate_normal(vars, player, map);
	}
}

void	animate_fall(t_var *vars, t_anim *player, t_map *map)
{
	char	tile_bellow;

	tile_bellow = map->tiles[player->position->y_tile + 1][player->position->x_tile];
	if (player->position->pos_on_tile == POS_UP 
		|| player->position->pos_on_tile == POS_LEFT
		|| player->position->pos_on_tile == POS_RIGHT)
	{
		player->position->pos_on_tile = POS_CENTER;
		player->direction = DIR_DOWN;
	}
	else if (tile_bellow == '0' || tile_bellow == 'C' )
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
		vars->game->player->timestamp = current_timestamp;
		if (vars->game->player->direction == DIR_LEFT)
		{
			vars->game->player->position->x_tile +=1;
			vars->game->player->position->pos_on_tile = POS_LEFT;
		}
		if (vars->game->player->direction == DIR_RIGHT)
		{
			vars->game->player->position->x_tile -=1;
			vars->game->player->position->pos_on_tile = POS_RIGHT;
		}
		if (vars->game->player->direction == DIR_UP)
		{
			vars->game->player->position->y_tile +=1;
		}
		vars->game->player->timestamp = current_timestamp;
	}
	if (current_timestamp - vars->game->player->timestamp < 200)
		return ;
	if (vars->game->player->movement == WALK)
	{
		animate_walk(vars, vars->game->player, vars->map);
		vars->game->player->timestamp = current_timestamp;
	}
	if (vars->game->player->movement == JUMP)
	{
		animate_jump(vars, vars->game->player, vars->map);
		vars->game->player->timestamp = current_timestamp;
	}
		if (vars->game->player->movement == FALL)
	{
		animate_fall(vars, vars->game->player, vars->map);
		vars->game->player->timestamp = current_timestamp;
	}
	if (current_timestamp - vars->game->player->timestamp < 700)
		return ;
	if (vars->game->player->movement == NORMAL)
	{
		animate_normal(vars, vars->game->player, vars->map);
		vars->game->player->timestamp = current_timestamp;
	}
//	ft_printf("movement : %d - dir : %d - anim_frame : %d ", vars->game->player->movement, vars->game->player->direction, vars->game->player->anim_frame);
//	ft_printf("- pos tile : %d - x_tile : %d\n", vars->game->player->position->pos_on_tile,  vars->game->player->position->x_tile);
}

/*
void	animate_player(t_game *game)
{
    struct 			timeval te;
	unsigned int	milliseconds;
	
    gettimeofday(&te, NULL); // get current time
    milliseconds = (unsigned int)(te.tv_sec*1000LL + te.tv_usec/1000) % DELAY;
	if (game->player->movement == NORMAL)
	{
		if (milliseconds < DELAY / 2)
			game->player->anim_frame = 0;
		else 
			game->player->anim_frame = 1;
	}
	if (game->player->movement == WALK)
	{
		if ((milliseconds + DELAY - game->time_anim) % DELAY < DELAY / 4)
		{
			game->player->anim_frame = 0;
		}	
		else if ((milliseconds + DELAY - game->time_anim) % DELAY < 2 * DELAY / 4)
		{
			game->player->anim_frame = 1;
		}
		else if ((milliseconds + DELAY - game->time_anim) % DELAY < 3 * DELAY / 4)
		{
			game->player->anim_frame = 2;
		}
		else 
			{
				game->player->anim_frame = 3;
				game->player->movement = NORMAL;
			}
	}
}
*/