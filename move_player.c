/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 20:03:57 by lpaquatt          #+#    #+#             */
/*   Updated: 2024/01/19 17:06:10 by lpaquatt         ###   ########.fr       */
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
	if (move_y == -1 && vars->game->player->position->pos_on_tile != POS_UP)
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

int	update_nb_moves(t_var *vars)
{
	char	*str_moves;

	vars->game->moves++;
	if (vars->game->nb_moves)
		free (vars->game->nb_moves);
	str_moves = ft_itoa(vars->game->moves);
	if (!str_moves)
		return (ft_printf(ERROR_MALLOC), EXIT_FAILURE);
	vars->game->nb_moves = ft_strjoin("Number of moves : ", str_moves);
	if (!vars->game->nb_moves)
		return (free(str_moves), ft_printf(ERROR_MALLOC), EXIT_FAILURE);
	free(str_moves);
	ft_printf("Number of moves : %d\n", vars->game->moves);
	return (EXIT_SUCCESS);
}

int	player_is_moving(t_var *vars, int move_x, int move_y)
{
	move_on_tiles(vars, move_x, move_y);
	if (move_x != 0)
		update_player_on_x(vars, move_x);
	if (move_y != 0)
		update_player_on_y(vars, move_y);
	if (update_nb_moves(vars) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	move_player(t_var *vars, int move_x, int move_y)
{
	int	x;
	int	y;

	x = vars->game->player->position->x_tile;
	y = vars->game->player->position->y_tile;
	if (vars->game->end_of_game == 1 || vars->game->end_of_game == -1)
		return (EXIT_SUCCESS);
	if (move_y == -1 && vars->game->player->position->pos_on_tile == POS_UP
		&& vars->map->tiles[y - 1 + move_y][x + move_x] == '1')
	{
		move_on_tiles (vars, move_x, move_y);
		vars->game->player->position->pos_on_tile = POS_CENTER;
		return (EXIT_SUCCESS);
	}
	if (vars->map->tiles[y + move_y][x + move_x] == 'C'
		|| vars->map->tiles[y + move_y][x + move_x] == '0'
		|| vars->map->tiles[y + move_y][x + move_x] == 'M')
	{
		if (player_is_moving(vars, move_x, move_y) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (vars->map->tiles[y + move_y][x + move_x] == 'e')
		display_victory(vars, move_x, move_y);
	return (EXIT_SUCCESS);
}
