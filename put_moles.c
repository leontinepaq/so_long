/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_moles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:16:25 by lpaquatt          #+#    #+#             */
/*   Updated: 2024/01/26 15:17:22 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

int	animate_mole(int x, int y, int *row, int *col)
{
	struct timeval	te;
	time_t			current_timestamp;

	if (gettimeofday(&te, NULL) == -1)
		return (ft_printf(ERROR_GETTIME), EXIT_FAILURE);
	current_timestamp = (time_t)((te.tv_sec * 1000) + te.tv_usec / 1000);
	current_timestamp += fmod(sin(x) + cos(y), 1.0) * 8000;
	if (current_timestamp % 8000 > 4500)
	{
		*row = 1;
		*col = 0;
	}
	else
	{
		*row = 0;
		*col = 0;
		while ((*col + 1) * 300 < current_timestamp % 8000)
			*col += 1;
	}
	return (EXIT_SUCCESS);
}

int	put_one_mole(t_var *vars, int x, int y)
{
	t_img	*mole;
	int		row;
	int		col;

	row = 0;
	col = 0;
	if (animate_mole(x, y, &row, &col) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	mole = crop_sprite(vars->assets->mole, vars, row, col);
	if (!mole)
		return (EXIT_FAILURE);
	overlap_image(vars, mole, x * TILE_SIZE * vars->scale,
		y * TILE_SIZE * vars->scale);
	mlx_destroy_image(vars->mlx, mole->img_ptr);
	free(mole);
	return (EXIT_SUCCESS);
}

int	put_moles(t_var *vars)
{
	int	x;
	int	y;

	y = 0;
	while (y < vars->map->height)
	{
		x = 0;
		while (x < vars->map->width)
		{
			if (vars->map->tiles[y][x] == 'M' || vars->map->tiles[y][x] == 'm')
			{
				if (put_one_mole(vars, x, y) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			}
			x++;
		}
		y++;
	}
	return (EXIT_SUCCESS);
}
