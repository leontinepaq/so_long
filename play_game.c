/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:26:03 by lpaquatt          #+#    #+#             */
/*   Updated: 2024/01/19 17:03:58 by lpaquatt         ###   ########.fr       */
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
	move_on_tiles(vars, move_x, move_y);
	vars->game->end_of_game = 1;
	ft_printf("VICTORY !!!\nFinal number of moves : %d\n", vars->game->moves);
}

int	manage_keys(int keysym, t_var *vars)
{
	int	res;

	res = EXIT_SUCCESS;
	if (!vars->win)
		return (EXIT_FAILURE);
	if (keysym == XK_a || keysym == XK_Left)
		res += move_player(vars, -1, 0);
	else if (keysym == XK_d || keysym == XK_Right)
		res += move_player(vars, 1, 0);
	else if (keysym == XK_w || keysym == XK_Up)
		res += move_player(vars, 0, -1);
	else if (keysym == XK_s || keysym == XK_Down)
		res += move_player(vars, 0, 1);
	else if (keysym == XK_Escape)
		close_window(vars);
	if (res > 0)
		return (close_window(vars), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
