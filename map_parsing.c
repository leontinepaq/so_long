/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:37:17 by lpaquatt          #+#    #+#             */
/*   Updated: 2023/12/23 00:51:01 by lpaquatt         ###   ########.fr       */
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
			return (ft_printf(ERROR_MALLOC), EXIT_FAILURE);
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
	if (check_valid_path(map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	open_map(t_map *map)
{
	int		fd;

	map->content = NULL;
	map->tiles = NULL;
	fd = open("maps/map_big.ber", O_RDONLY);
	if (fd < 0)
		return (ft_printf("Error open\n"), EXIT_FAILURE);
	read_map(fd, map);
	close(fd);
	if (check_map(map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
