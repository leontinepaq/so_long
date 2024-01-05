/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:22:16 by lpaquatt          #+#    #+#             */
/*   Updated: 2024/01/05 14:54:49 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

/*
void	anim_landing(t_var *vars)
{
	vars->game->player->anim_frame = 6;
	render_img(vars);
	usleep(500000);
	vars->game->player->anim_frame = 7;
	render_img(vars);
	usleep(500000);
	vars->game->player->movement = NORMAL;
	vars->game->player->anim_frame = 0;
}

void	gravity(t_var *vars)
{
	int		x;
	int 	y;
	char	tile_bellow;

	if (vars->game->player->position->pos_on_tile == POS_UP)
	{
		usleep (200000);
		vars->game->player->position->pos_on_tile = POS_CENTER;
		return ;
	}
	if (vars->game->player->position->pos_on_tile == POS_CENTER)
	{
		x = vars->game->player->position->x_tile;
		y = vars->game->player->position->y_tile + 1;
		tile_bellow = vars->map->tiles[y][x];
		if (tile_bellow == '0' || tile_bellow == 'C')
		{
			usleep (150000);
			vars->game->player->position->pos_on_tile = POS_UP;
			move_player(vars, 0, 1);
			vars->game->player->movement = JUMP;
			vars->game->player->anim_frame = 5;
		}
		else
		{
			vars->game->player->movement = NORMAL;
			vars->game->player->anim_frame = 0;
		}
		/ *
			if (vars->game->player->movement == JUMP)
				anim_landing(vars);
		* /
	}
}
*/

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
//		player->movement = FALL;
		player->movement = NORMAL;
		player->anim_frame = 0;
	}
	else
		player->anim_frame += 2 * ((player->anim_frame + 1) % 2) - 1;
}

void	animate_walk(t_var *vars, t_anim *player, t_map *map)
{
	(void) vars;
	(void) map;
	player->anim_frame += 1;
	if (player->anim_frame == 1)
		player->position->pos_on_tile = POS_RIGHT;
	else if (player->anim_frame == 2)
	{
		player->position->pos_on_tile = POS_LEFT;
		player->position->x_tile += 1;
	}
	else if (player->anim_frame == 3)
		player->position->pos_on_tile = POS_CENTER;
	else if (player->anim_frame == 4)
	{
		player->movement = NORMAL;
		player->anim_frame = 0;
	}
	else if (player->anim_frame == 5)
		player->position->pos_on_tile = POS_LEFT;
	else if (player->anim_frame == 6)
	{
		player->position->pos_on_tile = POS_RIGHT;
		player->position->x_tile -= 1;
	}
	else if (player->anim_frame == 7)
		player->position->pos_on_tile = POS_CENTER;
	else if (player->anim_frame == 8)
	{
		player->movement = NORMAL;
		player->anim_frame = 2;
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
			vars->game->player->position->x_tile +=1;
		if (vars->game->player->direction == DIR_RIGHT)
			vars->game->player->position->x_tile -=1;
		if (vars->game->player->direction == DIR_UP)
			vars->game->player->position->y_tile +=1;
		animate_walk(vars, vars->game->player, vars->map);
	}
	if (current_timestamp - vars->game->player->timestamp < 300)
		return ;
	if (vars->game->player->movement == WALK)
	{
		animate_walk(vars, vars->game->player, vars->map);
		vars->game->player->timestamp = current_timestamp;
	}
	if (current_timestamp - vars->game->player->timestamp < 1000)
		return ;
	if (vars->game->player->movement == NORMAL)
		animate_normal(vars, vars->game->player, vars->map);
//	ft_printf("movement : %d - dir : %d - anim_frame : %d ", vars->game->player->movement, vars->game->player->direction, vars->game->player->anim_frame);
//	ft_printf("- pos tile : %d - x_tile : %d\n", vars->game->player->position->pos_on_tile,  vars->game->player->position->x_tile);
	vars->game->player->timestamp = current_timestamp;
	return ;
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