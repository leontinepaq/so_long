/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:17:33 by lpaquatt          #+#    #+#             */
/*   Updated: 2024/01/04 12:49:06 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

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
		return (free_assets(vars), free_vars(vars), EXIT_FAILURE);
	mlx_loop_hook(vars->mlx, &render, vars);
	mlx_hook(vars->win, KeyPress, KeyPressMask, &manage_keys, vars);
	mlx_hook(vars->win, ClientMessage, NoEventMask, &closure, vars);
	mlx_loop(vars->mlx);
	closure(vars);
	return (EXIT_SUCCESS);
}
