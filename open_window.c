/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:47:25 by lpaquatt          #+#    #+#             */
/*   Updated: 2024/01/18 16:06:37 by lpaquatt         ###   ########.fr       */
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
			"designs/AnimationSheet_Character4.xpm");
	vars->assets->background_1 = file_to_image(vars, "designs/Rock1.xpm");
	vars->assets->background_2 = file_to_image(vars, "designs/Rock2.xpm");
	vars->assets->background_3 = file_to_image(vars, "designs/Rock3.xpm");
	vars->assets->victory = file_to_image(vars, "designs/victory.xpm");
	vars->assets->mole = file_to_image(vars, "designs/mole2.xpm");
	if (!vars->assets->collectible
		|| !vars->assets->exit_close
		|| !vars->assets->exit_open
		|| !vars->assets->tile_ground
		|| !vars->assets->tile_wall
		|| !vars->assets->player
		|| !vars->assets->background_1
		|| !vars->assets->background_2
		|| !vars->assets->background_3
		|| !vars->assets->victory
		|| !vars->assets->mole)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	open_img(t_var *vars)
{
	vars->img->width = vars->map->width * TILE_SIZE * vars->scale;
	vars->img->height = (vars->map->height * TILE_SIZE + 16) * vars->scale;
	vars->img->img_ptr = mlx_new_image(vars->mlx,
			vars->img->width, vars->img->height);
	if (!vars->img->img_ptr)
		return (free(vars->img), close_window(vars),
			ft_printf(ERROR_MLX), EXIT_FAILURE);
	vars->img->img_pixels_ptr = mlx_get_data_addr(vars->img->img_ptr,
			&vars->img->bits_per_pixel,
			&vars->img->line_len, &vars->img->endian);
	return (EXIT_SUCCESS);
}

int	open_window(t_var *vars)
{
	int	w;
	int	h;

	w = vars->map->width * TILE_SIZE;
	h = vars->map->height * TILE_SIZE + 16;
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
	if (open_img(vars) == EXIT_FAILURE || open_assets(vars) == EXIT_FAILURE)
		return (closure(vars), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
