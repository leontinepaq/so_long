/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 19:18:02 by lpaquatt          #+#    #+#             */
/*   Updated: 2024/01/03 12:48:14 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

void	close_window(t_var *vars)
{
	if (vars->win)
	{
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
