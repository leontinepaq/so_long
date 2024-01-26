/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:47:25 by lpaquatt          #+#    #+#             */
/*   Updated: 2024/01/26 17:16:14 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

int	open_asset(t_var *vars, t_img **asset, char *path)
{
	*asset = file_to_image(vars, path);
	if (!*asset)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	open_assets(t_var *vars)
{
	int	res;

	res = EXIT_SUCCESS;
	res += open_asset(vars, &vars->assets->collectible, "designs/champi.xpm");
	res += open_asset(vars, &vars->assets->exit_close, "designs/exit_c.xpm");
	res += open_asset(vars, &vars->assets->exit_open, "designs/exit_o.xpm");
	res += open_asset(vars, &vars->assets->player, "designs/character.xpm");
	res += open_asset(vars, &vars->assets->tile_ground, "designs/ground.xpm");
	res += open_asset(vars, &vars->assets->tile_wall, "designs/wall.xpm");
	res += open_asset(vars, &vars->assets->background_1, "designs/rock1.xpm");
	res += open_asset(vars, &vars->assets->background_2, "designs/rock2.xpm");
	res += open_asset(vars, &vars->assets->background_3, "designs/rock3.xpm");
	res += open_asset(vars, &vars->assets->victory, "designs/victory.xpm");
	res += open_asset(vars, &vars->assets->game_over, "designs/game_over.xpm");
	res += open_asset(vars, &vars->assets->mole, "designs/mole.xpm");
	if (res != EXIT_SUCCESS)
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
		return (ft_printf(ERROR_MLX), EXIT_FAILURE);
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
	if (open_assets(vars) == EXIT_FAILURE || open_img(vars) == EXIT_FAILURE)
		return (closure(vars), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
