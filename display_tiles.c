/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_tiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:39:26 by lpaquatt          #+#    #+#             */
/*   Updated: 2023/12/23 00:49:00 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"



int	create_tiles(t_map *map)
{
	int	y;
	int	i;
	char	**tiles;
	
	tiles = malloc((map->height) * sizeof(char *));
	if (!tiles)
		return (ft_printf(ERROR_MALLOC), EXIT_FAILURE);
	map->tiles = tiles;
	y = 0;
	while (y < map->height)
	{
		tiles[y] = malloc((map->width + 1) * sizeof(char));
		if (!(tiles[y]))
			return (ft_printf(ERROR_MALLOC), EXIT_FAILURE);
		y++;
	}
	i = 0;
	while (map->content[i])
	{
		if (map->content[i] != '\n')
		{
			tiles[i / (map->width + 1)][i % (map->width + 1)] = map->content[i];
		}
		i++;
	}
	i = 0;
	while (i < map->height)
	{
		(tiles)[i][map->width] = 0;
		i++;
	}
	return (EXIT_SUCCESS);
}

int	display_one_tile(char type, int x, int y, t_var vars)
{
	(void) type;
	(void) x;
	(void) y;
	(void) vars;
	return (EXIT_SUCCESS);
}

int	display_tiles(t_map *map, t_var *vars)
{
	int		x;
	int		y;

	(void) vars;

	if (create_tiles(map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			//display_one_tile(tiles[y][x], x, y, vars);
			x++;
		}
		y++;
	}
	return (EXIT_SUCCESS);
}
