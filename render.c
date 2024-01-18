/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 23:19:41 by lpaquatt          #+#    #+#             */
/*   Updated: 2024/01/18 17:46:27 by lpaquatt         ###   ########.fr       */
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

void	put_tiles(t_var *vars)
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
}

void	put_nb_moves(t_var *vars)
{
	int	x;
	int	y;

	y = vars->map->height * TILE_SIZE * vars->scale + 1;
	while (y < (vars->map->height * TILE_SIZE + 16) * vars->scale)
	{
		x = 0;
		while (x < vars->map->width * TILE_SIZE * vars->scale)
		{
			my_pixel_put(vars->img, x, y, 0x2d1f12);
			x++;
		}
		y++;
	}
	
}
void	check_game_over(t_var *vars)
{
	int				x;
	int				y;
	struct timeval	te;
	time_t			current_timestamp;

	x = vars->game->player->position->x_tile;
	y = vars->game->player->position->y_tile;
	if (vars->map->tiles[y][x] == 'm'
		&& vars->game->player->movement != DEATH)
	{
		gettimeofday(&te, NULL);
		current_timestamp = (time_t)((te.tv_sec * 1000) + te.tv_usec / 1000);
		current_timestamp += fmod(sin(x) + cos(y), 1.0) * 8000;
		if (current_timestamp % 8000 > 2100 && current_timestamp % 8000 < 4500
			&& vars->game->player->position->pos_on_tile == POS_CENTER)
		{
			vars->game->player->movement = DEATH;
			vars->game->player->anim_frame = 0;
			vars->game->end_of_game = -1;
			if (vars->game->player->direction == DIR_LEFT)
				vars->game->player->anim_frame = 7;
		}
	}
}

void	display_end_of_game(t_var *vars)
{
	t_img	*message;
	
	if (vars->game->end_of_game == 1)
		message = vars->assets->victory;
	else
		message = vars->assets->game_over;
	overlap_image(vars, message,
		(vars->game->player->position->x_tile - 1) * TILE_SIZE * vars->scale,
		(vars->game->player->position->y_tile - 1) * TILE_SIZE * vars->scale);
}

int	render(t_var *vars)
{
	if (!vars->win)
		return (EXIT_FAILURE);
	animate_player(vars);
	put_background(vars);
	put_tiles(vars);
	if (put_moles(vars) == EXIT_FAILURE || put_player(vars) == EXIT_FAILURE)
		return (close_window(vars), EXIT_FAILURE);
	put_nb_moves(vars);
	check_game_over(vars);
	if (vars->game->end_of_game == 1 || vars->game->end_of_game == -1)
		display_end_of_game(vars);
	if (mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img_ptr, 0, 0)
		== EXIT_FAILURE)
		return (ft_printf(ERROR_MLX), EXIT_FAILURE);
	mlx_string_put(vars->mlx,
		vars->win, vars->map->width * TILE_SIZE * vars->scale / 2 - 32,
		(vars->map->height * TILE_SIZE + 10) * vars->scale, 0xffffff, vars->game->nb_moves);
	return (EXIT_SUCCESS);
}
