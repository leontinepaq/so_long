/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_color_map.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:36:56 by lpaquatt          #+#    #+#             */
/*   Updated: 2024/01/10 14:46:51 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

int	color_cell(char *map, int cell)
{
	if (map[cell] != '1' && map[cell] != '@'
		&& map[cell] != 'E' && map[cell] != '\n')
	{
		map[cell] = '@';
		return (1);
	}
	return (0);
}

int	color_adjacent_cells(char *map, int cell, int width, int height)
{
	int	nb_colored;

	nb_colored = 0;
	if (cell % (width + 1) != 0)
		nb_colored += color_cell(map, cell - 1);
	if (cell % (width + 1) != width - 1 && cell % (width + 1) != width)
		nb_colored += color_cell(map, cell + 1);
	if (cell > width)
		nb_colored += color_cell(map, cell - (width + 1));
	if (cell < (width + 1) * (height - 1))
		nb_colored += color_cell(map, cell + (width + 1));
	return (nb_colored);
}

int	color_map_cells(char *map, int width, int height)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i] == '@')
		{
			if (color_adjacent_cells(map, i, width, height) > 0)
				return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

void	init_colored_map(char *map)
{
	int	i;

	i = 0;
	while (map[i] != 'P')
		i++;
	map[i] = '@';
}

void	color_map(char *map, int width, int height)
{
	init_colored_map(map);
	while (TRUE)
	{
		if (color_map_cells(map, width, height) == TRUE)
			break ;
	}
}
