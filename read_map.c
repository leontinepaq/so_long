/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:02:36 by lpaquatt          #+#    #+#             */
/*   Updated: 2024/01/26 17:04:54 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

void	end_gnl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}

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
		return (end_gnl(fd), free(line), ft_printf(ERROR_MALLOC), EXIT_FAILURE);
	map->width = ft_strlen(line)-1;
	while (line)
	{
		free(line);
		map->height++;
		line = get_next_line(fd);
		tmp = ft_strjoin(map->content, line);
		if (!tmp)
			return (end_gnl(fd), free(line),
				ft_printf(ERROR_MALLOC), EXIT_FAILURE);
		free(map->content);
		map->content = tmp;
	}
	return (EXIT_SUCCESS);
}
