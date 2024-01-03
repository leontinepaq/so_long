/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:52:31 by lpaquatt          #+#    #+#             */
/*   Updated: 2024/01/03 12:54:29 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

int	open_assets(t_var *vars)
{
	vars->assets->collectible = file_to_image(vars, "designs/champ_final.xpm");
	vars->assets->exit_close = file_to_image(vars, "designs/exit_close.xpm");
	vars->assets->exit_open = file_to_image(vars, "designs/exit_open.xpm");
	vars->assets->tile_ground = file_to_image(vars, "designs/tile_ground.xpm");
	vars->assets->tile_wall = file_to_image(vars, "designs/tile_wall.xpm");
	vars->assets->player = file_to_image(vars,
			"designs/AnimationSheet_Character.xpm");
	vars->assets->background_1 = file_to_image(vars, "designs/Rock1.xpm");
	vars->assets->background_2 = file_to_image(vars, "designs/Rock2.xpm");
	vars->assets->background_3 = file_to_image(vars, "designs/Rock3.xpm");
	if (!vars->assets->collectible
		|| !vars->assets->exit_close
		|| !vars->assets->exit_open
		|| !vars->assets->tile_ground
		|| !vars->assets->tile_wall
		|| !vars->assets->player
		|| !vars->assets->background_1
		|| !vars->assets->background_2
		|| !vars->assets->background_3)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	open_window(t_var *vars)
{
	int	w;
	int	h;

	w = vars->map->width * TILE_SIZE;
	h = vars->map->height * TILE_SIZE;
	vars->scale = 1;
	if (2 * w < 2560 && 2 * h < 1440)
	{
		w *= 2;
		h *= 2;
		vars->scale = 2;
	}
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
	if (open_assets(vars) == EXIT_FAILURE)
		return (EXIT_FAILURE);
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
	vars->game->move_player = NORMAL;
	vars->game->time_anim = 0;
	vars->game->anim_player = 0;
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
		return (free_vars(vars), ft_printf(ERROR_MALLOC), NULL);
	vars->game = malloc(sizeof(t_game));
	if (!vars->game)
		return (free_vars(vars), ft_printf(ERROR_MALLOC), NULL);
	vars->assets = malloc(sizeof(t_assets));
	if (!vars->assets)
		return (free_vars(vars), ft_printf(ERROR_MALLOC), NULL);
	return (vars);
}
