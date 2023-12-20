/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:51:52 by lpaquatt          #+#    #+#             */
/*   Updated: 2023/12/20 12:07:02 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

int	open_window(t_var *vars, t_map *map)
{
	int	w;
	int	h;

	w = map->width * 64;
	h = map->height * 64;
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (ft_printf(ERROR_MALLOC), EXIT_FAILURE);
	vars->win = mlx_new_window(vars->mlx, w, h, "Game");
	if (!vars->win)
	{
		mlx_destroy_display(vars->mlx);
		free (vars->mlx);
		return (ft_printf(ERROR_MALLOC), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	close_window(t_var *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free (vars->mlx);
}


void	free_tiles(t_map *map)
{
	int	y;

	if (!map->tiles)
		return ;
	y = 0;
	while (y < map->height && map->tiles[y])
	{
		free(map->tiles[y]);
		y++;
	}
	free(map->tiles);
}
void	free_map(t_map *map)
{
	if (map->content)
		free(map->content);
	if	(map->tiles)
		free_tiles(map);
	if (map)
		free(map);
}

int	escape(int keysym, t_var *vars)
{
	if (keysym == XK_Escape)
	{
		close_window(vars);
		free(vars);
		exit(1);
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
	if (open_map(map) == EXIT_FAILURE)
		return (free_map(map), free(vars), EXIT_FAILURE);
	if (open_window(vars, map) == EXIT_FAILURE)
		return (free_map(map), free(vars), EXIT_FAILURE);
	if (display_tiles(map, vars) == EXIT_FAILURE)
		return (free_map(map), close_window(vars), free(vars), EXIT_FAILURE);
	free_map(map);
	mlx_key_hook(vars->win, escape, vars);
	mlx_loop(vars->mlx);
	close_window(vars);
	free(vars);
	return (EXIT_SUCCESS);
}
