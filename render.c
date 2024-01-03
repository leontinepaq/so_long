/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 23:19:41 by lpaquatt          #+#    #+#             */
/*   Updated: 2024/01/03 13:01:46 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

void	put_specific_tile(int x, int y, t_var *vars)
{
	if (vars->map->tiles[y][x] == '1'
		&& y > 1 && vars->map->tiles[y - 1][x] != '1')
		overlap_image(vars, vars->assets->tile_ground,
			((x * TILE_SIZE) - OVERLAP_SIZE) * vars->scale,
			((y * TILE_SIZE) - OVERLAP_SIZE) * vars->scale);
	else if (vars->map->tiles[y][x] == '1')
		overlap_image(vars, vars->assets->tile_wall,
			((x * TILE_SIZE) - OVERLAP_SIZE) * vars->scale,
			((y * TILE_SIZE) - OVERLAP_SIZE) * vars->scale);
	else if (vars->map->tiles[y][x] == 'C')
		overlap_image(vars, vars->assets->collectible,
			((x * TILE_SIZE) - OVERLAP_SIZE) * vars->scale,
			((y * TILE_SIZE) - OVERLAP_SIZE) * vars->scale);
	else if (vars->map->tiles[y][x] == 'E')
		overlap_image(vars, vars->assets->exit_close,
			((x * TILE_SIZE) - OVERLAP_SIZE) * vars->scale,
			((y * TILE_SIZE) - OVERLAP_SIZE) * vars->scale);
	else if (vars->map->tiles[y][x] == 'e')
		overlap_image(vars, vars->assets->exit_open,
			((x * TILE_SIZE) - OVERLAP_SIZE) * vars->scale,
			((y * TILE_SIZE) - OVERLAP_SIZE) * vars->scale);
}

int	put_tiles(t_var *vars)
{
	int	x;
	int	y;
	int	x_exit;
	int	y_exit;

	y = 0;
	while (y < vars->map->height)
	{
		x = 0;
		while (x < vars->map->width)
		{
			if (vars->map->tiles[y][x] == 'E' || vars->map->tiles[y][x] == 'e')
			{
				x_exit = x;
				y_exit = y;
			}
			put_specific_tile(x, y, vars);
			x++;
		}
		y++;
	}
	put_specific_tile(x_exit, y_exit, vars);
	return (EXIT_SUCCESS);
}

int	render(t_var *vars)
{
	if (!vars->win)
		return (EXIT_FAILURE);
	vars->img = malloc(sizeof(t_img));
	if (!vars->img)
		return (close_window(vars), ft_printf(ERROR_MALLOC), EXIT_FAILURE);
	vars->img->width = vars->map->width * TILE_SIZE * vars->scale;
	vars->img->height = vars->map->height * TILE_SIZE * vars->scale;
	vars->img->img_ptr = mlx_new_image(vars->mlx,
			vars->img->width, vars->img->height);
	if (!vars->img->img_ptr)
		return (free(vars->img), close_window(vars),
			ft_printf(ERROR_MLX), EXIT_FAILURE);
	vars->img->img_pixels_ptr = mlx_get_data_addr(vars->img->img_ptr,
			&vars->img->bits_per_pixel,
			&vars->img->line_len, &vars->img->endian);
	if (put_background(vars) == EXIT_FAILURE
		|| put_tiles(vars) == EXIT_FAILURE
		|| put_player(vars) == EXIT_FAILURE)
	{
		mlx_destroy_image(vars->mlx, vars->img->img_ptr);
		return (close_window(vars), free(vars->img), EXIT_FAILURE);
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img_ptr, 0, 0);
	mlx_destroy_image(vars->mlx, vars->img->img_ptr);
	return (free(vars->img), EXIT_SUCCESS);
}
