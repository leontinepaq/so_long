/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:17:33 by lpaquatt          #+#    #+#             */
/*   Updated: 2023/12/23 00:41:40 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"


int	open_window(t_var *vars, t_map *map)
{
	int	w;
	int	h;

	w = map->width * TILE_SIZE; 
	h = map->height * TILE_SIZE;
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





int	main(void)
{
	t_map	*map;
	t_var	*vars;
	
	map = malloc(sizeof(t_map)); 
	if (!map)
		return (ft_printf(ERROR_MALLOC), EXIT_FAILURE);
	vars = malloc(sizeof(t_var));
	if (!vars)
		return (free(map), ft_printf(ERROR_MALLOC), EXIT_FAILURE);
	vars->map = map;
	if (open_map(map) == EXIT_FAILURE)
		return (free_map(map), free(vars), EXIT_FAILURE);
	if (open_window(vars, map) == EXIT_FAILURE)
		return (free_map(map), free(vars), EXIT_FAILURE);

	if (display_tiles(map, vars) == EXIT_FAILURE)
		return (free_map(map), close_window(vars), free(vars), EXIT_FAILURE);
	
	mlx_loop_hook(vars->mlx, &render, vars);
	mlx_hook(vars->win, KeyPress, KeyPressMask, &escape, vars);
	mlx_hook(vars->win, ClientMessage, NoEventMask, &closure, vars);
	
	mlx_loop(vars->mlx);
	closure(vars);
	return (EXIT_SUCCESS);
}



