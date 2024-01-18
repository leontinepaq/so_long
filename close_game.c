/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 19:18:02 by lpaquatt          #+#    #+#             */
/*   Updated: 2024/01/18 22:21:51 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

void	check_game_over(t_var *vars)
{
	int				x;
	int				y;
	struct timeval	te;
	time_t			current_timestamp;

	x = vars->game->player->position->x_tile;
	y = vars->game->player->position->y_tile;
	if (vars->map->tiles[y][x] == 'm'
		&& vars->game->player->movement != DEATH)
	{
		gettimeofday(&te, NULL);
		current_timestamp = (time_t)((te.tv_sec * 1000) + te.tv_usec / 1000);
		current_timestamp += fmod(sin(x) + cos(y), 1.0) * 8000;
		if (current_timestamp % 8000 > 2100 && current_timestamp % 8000 < 4500
			&& vars->game->player->position->pos_on_tile == POS_CENTER)
		{
			vars->game->player->movement = DEATH;
			vars->game->player->anim_frame = 0;
			vars->game->end_of_game = -1;
			if (vars->game->player->direction == DIR_LEFT)
				vars->game->player->anim_frame = 7;
		}
	}
}

void	display_end_of_game(t_var *vars)
{
	t_img	*message;

	if (vars->game->end_of_game == 1)
		message = vars->assets->victory;
	else
		message = vars->assets->game_over;
	overlap_image(vars, message,
		(vars->game->player->position->x_tile - 1) * TILE_SIZE * vars->scale,
		(vars->game->player->position->y_tile - 1) * TILE_SIZE * vars->scale);
}

void	close_window(t_var *vars)
{
	if (vars->win)
	{
		if (vars->img)
		{
			if (vars->img->img_ptr)
				mlx_destroy_image(vars->mlx, vars->img->img_ptr);
		}
		mlx_destroy_window(vars->mlx, vars->win);
		vars->win = NULL;
	}
}

int	closure(t_var *vars)
{
	close_window(vars);
	if (vars->assets)
		free_assets(vars);
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
