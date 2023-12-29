/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:17:33 by lpaquatt          #+#    #+#             */
/*   Updated: 2023/12/29 21:58:00 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

int	open_window(t_var *vars)
{
	int	w;
	int	h;

	w = vars->map->width * TILE_SIZE;
	h = vars->map->height * TILE_SIZE;
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (ft_printf(ERROR_MLX), EXIT_FAILURE);
	vars->win = mlx_new_window(vars->mlx, w, h, "Game");
	if (!vars->win)
	{
		mlx_destroy_display(vars->mlx);
		free (vars->mlx);
		return (ft_printf(ERROR_MLX), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
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
				vars->game->x_player = x;
				vars->game->y_player = y;
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
	find_special_items(vars);
	return (EXIT_SUCCESS);
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
	vars->game = malloc(sizeof(t_game));
	if (!vars->game)
		return (free(vars->map), free(vars), ft_printf(ERROR_MALLOC), NULL);
	return (vars);
}

int	main(void)
{
	t_var	*vars;

	vars = malloc_vars();
	if (!vars)
		return (EXIT_FAILURE);
	if (open_map(vars->map) == EXIT_FAILURE)
		return (free_vars(vars), EXIT_FAILURE);
	if (init_game(vars) == EXIT_FAILURE)
		return (free_vars(vars), EXIT_FAILURE);
	if (open_window(vars) == EXIT_FAILURE)
		return (free_vars(vars), EXIT_FAILURE);
	mlx_loop_hook(vars->mlx, &render, vars);
	mlx_hook(vars->win, KeyPress, KeyPressMask, &manage_keys, vars);
	mlx_hook(vars->win, ClientMessage, NoEventMask, &closure, vars);
	mlx_loop(vars->mlx);

	closure(vars);
	return (EXIT_SUCCESS);
}
