/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:26:03 by lpaquatt          #+#    #+#             */
/*   Updated: 2023/12/29 16:30:01 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

void	open_exit(t_var *vars)
{
	int	x;
	int	y;

	x = 0;
	while (x < vars->map->width)
	{
		y = 0;
		while (y < vars->map->height)
		{
			if (vars->map->tiles[y][x] == 'E')
			{
				vars->map->tiles[y][x] = 'e';
				break ;
			}
			y++;
		}
		x++;
	}
}

void	display_victory(t_var *vars, int move_x, int move_y)
{
	vars->map->tiles[vars->game->y_player][vars->game->x_player] = '0';
	vars->game->x_player += move_x;
	vars->game->y_player += move_y;
	vars->game->end_of_game = 1;
	ft_printf("VICTORY !!!\n");
}

void	move_player(t_var *vars, int move_x, int move_y)
{
	int	x;
	int	y;

	if (vars->game->end_of_game == 1)
		return ;
	x = vars->game->x_player;
	y = vars->game->y_player;
	if (vars->map->tiles[y + move_y][x + move_x] == 'C'
		|| vars->map->tiles[y + move_y][x + move_x] == '0')
	{
		if (vars->map->tiles[y + move_y][x + move_x] == 'C')
		{
			vars->game->collectibles--;
			if (vars->game->collectibles == 0)
				open_exit(vars);
		}
		vars->map->tiles[y + move_y][x + move_x] = 'P';
		vars->map->tiles[y][x] = '0';
		vars->game->x_player += move_x;
		vars->game->y_player += move_y;
		vars->game->moves++;
	}
	else if (vars->map->tiles[y + move_y][x + move_x] == 'e')
		display_victory(vars, move_x, move_y);
}

int	manage_keys(int keysym, t_var *vars)
{
	if (keysym == XK_a || keysym == XK_Left)
	{
		move_player(vars, -1, 0);
	}
	else if (keysym == XK_d || keysym == XK_Right)
	{
		move_player(vars, 1, 0);
	}
	else if (keysym == XK_w || keysym == XK_Up)
	{
		move_player(vars, 0, -1);
	}
	else if (keysym == XK_s || keysym == XK_Down)
	{
		move_player(vars, 0, 1);
	}
	else if (keysym == XK_Escape)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		vars->win = NULL;
	}
	return (EXIT_SUCCESS);
}
