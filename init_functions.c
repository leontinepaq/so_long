/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:52:31 by lpaquatt          #+#    #+#             */
/*   Updated: 2024/01/19 16:52:27 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

t_var	*malloc_game(t_var *vars)
{
	vars->game = malloc(sizeof(t_game));
	if (!vars->game)
		return (free(vars->map), free(vars), ft_printf(ERROR_MALLOC), NULL);
	vars->game->player = malloc(sizeof(t_anim));
	if (! vars->game->player)
	{
		free(vars->game);
		free(vars->map);
		free(vars);
		return (ft_printf(ERROR_MALLOC), NULL);
	}
	vars->game->player->position = malloc(sizeof(t_pos));
	if (!vars->game->player->position)
	{
		free(vars->game->player);
		free(vars->game);
		free(vars->map);
		free(vars);
		return (ft_printf(ERROR_MALLOC), NULL);
	}
	vars->game->nb_moves = NULL;
	return (vars);
}

t_var	*malloc_vars(void)
{
	t_var	*vars;

	vars = malloc(sizeof(t_var));
	if (!vars)
		return (ft_printf(ERROR_MALLOC), NULL);
	vars->map = malloc(sizeof(t_map));
	if (!vars->map)
		return (free(vars), ft_printf(ERROR_MALLOC), NULL);
	vars->map->content = NULL;
	vars->map->tiles = NULL;
	if (malloc_game(vars) == NULL)
		return (NULL);
	vars->img = malloc(sizeof(t_img));
	if (!vars->img)
	{
		free(vars->game->player->position);
		free(vars->game->player);
		free(vars->game);
		free(vars->map);
		return (free(vars), ft_printf(ERROR_MALLOC), NULL);
	}
	vars->assets = malloc(sizeof(t_assets));
	if (!vars->assets)
		return (free_vars(vars), ft_printf(ERROR_MALLOC), NULL);
	return (vars);
}

void	find_special_items(t_var *vars)
{
	int	x;
	int	y;

	y = 0;
	while (y < vars->map->height)
	{
		x = 0;
		while (x < vars->map->width)
		{
			if (vars->map->tiles[y][x] == 'P')
			{
				vars->game->player->position->x_tile = x;
				vars->game->player->position->y_tile = y;
				vars->game->player->position->pos_on_tile = POS_CENTER;
			}
			if (vars->map->tiles[y][x] == 'C')
				vars->game->collectibles++;
			x++;
		}
		y++;
	}	
}

int	init_game(t_var *vars)
{
	vars->game->collectibles = 0;
	vars->game->moves = -1;
	vars->game->nb_moves = NULL;
	if (update_nb_moves(vars) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	vars->game->end_of_game = 0;
	vars->game->player->timestamp = 0;
	vars->game->player->movement = NORMAL;
	vars->game->player->direction = DIR_RIGHT;
	vars->game->player->anim_frame = 0;
	find_special_items(vars);
	return (EXIT_SUCCESS);
}
