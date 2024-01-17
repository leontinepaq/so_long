/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:37:17 by lpaquatt          #+#    #+#             */
/*   Updated: 2024/01/17 16:42:28 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

int	read_map(int fd, t_map *map)
{
	char	*line;
	char	*tmp;

	map->height = 0;
	line = get_next_line(fd);
	if (!line)
		return (ft_printf(ERROR_MAP_MESS"Empty map\n"), EXIT_FAILURE);
	map->content = ft_strdup(line);
	if (!map->content)
		return (ft_printf(ERROR_MALLOC), EXIT_FAILURE);
	map->width = ft_strlen(line)-1;
	while (line)
	{
		free(line);
		map->height++;
		line = get_next_line(fd);
		if (!line)
			break ;
		tmp = ft_strjoin(map->content, line);
		if (!tmp)
			return (free(line), ft_printf(ERROR_MALLOC), EXIT_FAILURE);
			// leaks lies au  get nextline non fini d'etre lu
		free(map->content);
		map->content = tmp;
	}
	return (EXIT_SUCCESS);
}

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

int	open_map(t_map *map)
{
	int		fd;

	map->content = NULL;
	map->tiles = NULL;
	fd = open("maps/map_test.ber", O_RDONLY);
	if (fd < 0)
		return (ft_printf("Error\nProblem reading the map\n"), EXIT_FAILURE);
	if (read_map(fd, map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	close(fd);
	if (check_map(map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (create_tiles(map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
