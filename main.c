/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:17:33 by lpaquatt          #+#    #+#             */
/*   Updated: 2024/01/26 15:17:59 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

int	main(int ac, char **av)
{
	t_var	*vars;
	char	*map_path;

	if (ac == 1)
		map_path = "maps/map_test.ber";
	else if (ac == 2)
		map_path = av[1];
	else
		return (ft_printf("Error\n Too many arguments"), EXIT_FAILURE);
	vars = malloc_vars();
	if (!vars)
		return (EXIT_FAILURE);
	if (open_map(vars->map, map_path) == EXIT_FAILURE)
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
