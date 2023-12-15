/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_tiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:02:45 by lpaquatt          #+#    #+#             */
/*   Updated: 2023/12/15 18:54:24 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

typedef struct s_tile
{
	int		x;
	int		y;
	char	type;
	char	og_type;
	t_tile	*left;
	t_tile	*right;
	t_tile	*up;
	t_tile	*down;
}				t_tile;

t_tile	*fill_tile(t_map *map, int i)
{
	
}

t_tile *find_tile(t_tile **tiles_map, int target, int width)
{
	int 	i;
	t_tile	*tile;

	if (!tiles_map)
		return (NULL);
	i = 0;
	tile = *tiles_map;
	while (tile->x != i % (width + 1) && tile->y != i / (width +1))
	{
		if (!tile->right && !tile->down)
			return(NULL);
		if (i % (width + 1) != width && )
	}
	return (tile)
}

int	create_tile(t_tile **tiles_map, t_map *map, int i)
{
	if (i % (map->width + 1) == map->width)
		return (EXIT_SUCCESS);
	else if (i == 0)
		*tiles_map = fill_tile(map, i); ///a proteger
	else if (i % (map->height + 1) != 0)
	{
		find_tile(tiles_map, i - 1, map->width)->right = fill_tile(map, i);
	}
	else if (i % (map->height + 1) == 0)
	{
		find_tile(tiles_map, i - map->width, map->width)->down = fill_tile(map, i);
	}
	
}

int	link_tiles(t_tile **tiles_map)
{
	
}

int	create_tile_map(t_tile **tiles_map, t_map *map)
{
	int	i;
	
	i = 0;
	while (map->content[i])
	{
		if (create_tile(tiles_map, map, i) == EXIT_FAILURE)
			return(EXIT_FAILURE);
		i++;
	}
	link_tiles(tiles_map);
	return(EXIT_SUCCESS);
}

int display_tiles(t_map *map)
{
	t_tile	**tiles_map;
	
	tiles_map = malloc(sizeof(t_tile **));
	if (!tiles_map)
		return (ft_printf('Error malloc\n'), EXIT_FAILURE);
	if (create_tile_map(tiles_map, map) == EXIT_FAILURE)
		return (free(tiles_map), EXIT_FAILURE); //free tiles 1 par 1
	free(tiles_map); //free tiles 1 par 1
	return (EXIT_SUCCESS);
}
