/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:37:17 by lpaquatt          #+#    #+#             */
/*   Updated: 2024/01/26 17:03:01 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

int	check_map(t_map *map)
{
	if (check_size(map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_content_chars(map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_walls(map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_objects(map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_valid_path(map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	malloc_tiles(t_map *map)
{
	int	y;

	map->tiles = malloc((map->height) * sizeof(char *));
	if (!map->tiles)
		return (ft_printf(ERROR_MALLOC), EXIT_FAILURE);
	y = 0;
	while (y < map->height)
	{
		map->tiles[y] = malloc((map->width + 1) * sizeof(char));
		if (!(map->tiles[y]))
			return (ft_printf(ERROR_MALLOC), EXIT_FAILURE);
		y++;
	}
	return (EXIT_SUCCESS);
}

int	create_tiles(t_map *map)
{
	int	i;

	if (malloc_tiles(map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	i = 0;
	while (map->content[i])
	{
		if (map->content[i] != '\n')
		{
			map->tiles[i / (map->width + 1)][i % (map->width + 1)]
				= map->content[i];
		}
		i++;
	}
	i = 0;
	while (i < map->height)
	{
		(map->tiles)[i][map->width] = 0;
		i++;
	}
	return (EXIT_SUCCESS);
}

int	open_map(t_map *map, char *map_path)
{
	int		fd;

	map->content = NULL;
	map->tiles = NULL;
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Error\nProblem reading the map\n"), EXIT_FAILURE);
	if (read_map(fd, map) == EXIT_FAILURE)
		return (close(fd), EXIT_FAILURE);
	close(fd);
	if (check_map(map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (create_tiles(map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
