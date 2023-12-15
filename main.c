/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:51:52 by lpaquatt          #+#    #+#             */
/*   Updated: 2023/12/15 17:13:47 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

int	main(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (ft_printf("Error malloc"), EXIT_FAILURE);
	if (open_map(map) == EXIT_FAILURE)
		return (free(map), free(map->content), EXIT_FAILURE);
	if (display_tiles(map) == EXIT_FAILURE)
		return (free(map), free(map->content), EXIT_FAILURE);
	free(map->content);
	free(map);
	return (EXIT_FAILURE);
}
