/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:23:23 by lpaquatt          #+#    #+#             */
/*   Updated: 2024/01/19 12:46:50 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

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
		return (ft_printf(ERROR_MALLOC), EXIT_FAILURE);
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
