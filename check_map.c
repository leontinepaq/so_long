/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:30:39 by lpaquatt          #+#    #+#             */
/*   Updated: 2023/12/15 16:56:32 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

int	check_size(t_map *map)
{
	size_t	i;

	if (!map->content || map->height < 3 || map->width < 3)
		return (ft_printf(ERROR_MAP_MESS "Map too small\n"), EXIT_FAILURE);
	if (map->height > MAX_SIZE_MAP || map->width > MAX_SIZE_MAP)
		return (ft_printf(ERROR_MAP_MESS "Map too big\n"), EXIT_FAILURE);
	if (strlen(map->content) - (map->height - 1)
		!= (size_t)(map->height * map->width))
		return (ft_printf(ERROR_MAP_MESS ERROR_MAP_RECT), EXIT_FAILURE);
	i = 0;
	while (map->content[i])
	{
		if (i % (map->width + 1) == map->width && map->content[i] != '\n')
			return (ft_printf(ERROR_MAP_MESS ERROR_MAP_RECT), EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	check_content_chars(t_map *map)
{
	int	i;
	int	is_initial_position;
	int	is_collectible;
	int	is_exit;

	is_initial_position = 0;
	is_collectible = 0;
	is_exit = 0;
	i = 0;
	while (map->content[i])
	{
		if (map->content[i] == 'P')
			is_initial_position++;
		else if (map->content[i] == 'C')
			is_collectible++;
		else if (map->content[i] == 'E')
			is_exit++;
		else if (map->content[i] != '1' && map->content[i] != '0'
			&& map->content[i] != '\n')
			return (ft_printf(ERROR_MAP_MESS ERROR_MAP_UNKNOWN), EXIT_FAILURE);
		i++;
	}
	if (is_initial_position != 1 || is_collectible < 1 || is_exit != 1)
		return (ft_printf(ERROR_MAP_MESS ERROR_MAP_CONTAINS), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_walls(t_map *map)
{
	int	i;

	i = 0;
	while (map->content[i])
	{
		if ((i % (map->width + 1) == 0
				|| i % (map->width + 1) == map->width - 1
				|| i < map->width
				|| i >= (map->height - 1) * (map->width + 1))
			&& map->content[i] != '1')
			return (ft_printf(ERROR_MAP_MESS ERROR_MAP_WALLS), EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	check_exit(char *map, int width)
{
	int	i;

	i = 0;
	while (map[i] != 'E')
		i++;
	if (map[i - 1] == '@'
		|| map[i + 1] == '@'
		|| map[i - (width + 1)] == '@'
		|| map[i + (width + 1)] == '@')
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	check_valid_path(t_map *map)
{
	char	*colored_map;
	int		i;

	colored_map = ft_strdup(map->content);
	if (!colored_map)
		return (ft_printf("Error malloc\n"), EXIT_FAILURE);
	color_map(colored_map, map->width, map->height);
	i = 0;
	while (colored_map[i])
	{
		if (colored_map[i] == 'C')
		{
			free (colored_map);
			return (ft_printf(ERROR_MAP_MESS ERROR_MAP_PATH), EXIT_FAILURE);
		}
		i++;
	}
	if (check_exit(colored_map, map->width) == EXIT_FAILURE)
		return (ft_printf(ERROR_MAP_MESS ERROR_MAP_PATH), EXIT_FAILURE);
	free(colored_map);
	return (EXIT_SUCCESS);
}
