/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:52:31 by lpaquatt          #+#    #+#             */
/*   Updated: 2024/01/04 12:49:19 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

t_var	*malloc_vars(void)
{
	t_var	*vars;

	vars = malloc(sizeof(t_var));
	if (!vars)
		return (ft_printf(ERROR_MALLOC), NULL);
	vars->map = malloc(sizeof(t_map));
	if (!vars->map)
		return (free_vars(vars), ft_printf(ERROR_MALLOC), NULL);
	vars->game = malloc(sizeof(t_game));
	if (!vars->game)
		return (free_vars(vars), ft_printf(ERROR_MALLOC), NULL);
	vars->game->pos_player = malloc(sizeof(t_pos));
	if (!vars->game->pos_player)
		return (free_vars(vars), ft_printf(ERROR_MALLOC), NULL);
	vars->img = malloc(sizeof(t_img));
	if (!vars->img)
		return (free_vars(vars), ft_printf(ERROR_MALLOC), NULL);
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
				vars->game->pos_player->x_tile = x;
				vars->game->pos_player->y_tile = y;
				vars->game->pos_player->pos_on_tile = POS_CENTER;
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
	vars->game->moves = 0;
	vars->game->end_of_game = 0;
	vars->game->move_player = NORMAL;
	vars->game->time_anim = 0;
	vars->game->anim_player = 0;
	find_special_items(vars);
	return (EXIT_SUCCESS);
}