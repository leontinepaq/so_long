/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 23:19:41 by lpaquatt          #+#    #+#             */
/*   Updated: 2024/01/04 12:54:43 by lpaquatt         ###   ########.fr       */
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

int	render_img(t_var *vars)
{
	if (put_background(vars) == EXIT_FAILURE
		|| put_tiles(vars) == EXIT_FAILURE
		|| put_player(vars) == EXIT_FAILURE)
		return (close_window(vars), EXIT_FAILURE);
	if (mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img_ptr, 0, 0)
		== EXIT_FAILURE)
		return (ft_printf(ERROR_MLX), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	anim_landing(t_var *vars)
{
	vars->game->anim_player = 6;
	render_img(vars);
	usleep(500000);
	vars->game->anim_player = 7;
	render_img(vars);
	usleep(500000);
	vars->game->move_player = NORMAL;
	vars->game->anim_player = 0;
}

void	gravity(t_var *vars)
{
	int		x;
	int 	y;
	char	tile_bellow;

	if (vars->game->pos_player->pos_on_tile == POS_UP)
	{
		usleep (200000);
		vars->game->pos_player->pos_on_tile = POS_CENTER;
		return ;
	}
	if (vars->game->pos_player->pos_on_tile == POS_CENTER)
	{
		x = vars->game->pos_player->x_tile;
		y = vars->game->pos_player->y_tile + 1;
		tile_bellow = vars->map->tiles[y][x];
		if (tile_bellow == '0' || tile_bellow == 'C')
		{
			usleep (150000);
			vars->game->pos_player->pos_on_tile = POS_UP;
			move_player(vars, 0, 1);
			vars->game->move_player = JUMP;
			vars->game->anim_player = 5;
		}
		else
		{
			vars->game->move_player = NORMAL;
			vars->game->anim_player = 0;
		}
		/*
			if (vars->game->move_player == JUMP)
				anim_landing(vars);
		*/
	}
}

int	render(t_var *vars)
{
	if (!vars->win)
		return (EXIT_FAILURE);
	if (render_img(vars) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	gravity(vars);
	return (EXIT_SUCCESS);
}
