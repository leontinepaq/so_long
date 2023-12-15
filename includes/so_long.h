/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 01:06:01 by lpaquatt          #+#    #+#             */
/*   Updated: 2023/12/15 17:04:22 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>

# define ERROR_MAP_MESS "Error\nProblem with the configuration of the map : "
# define ERROR_MAP_RECT "Map is not rectangular\n"
# define ERROR_MAP_UNKNOWN "Unknown character\n"
# define ERROR_MAP_WALLS "Map must be closed by walls\n"
# define ERROR_MAP_PATH "No valid path found\n"
# define ERROR_MAP_CONTAINS "Must have 1 'P', at least 1 'C' and 1 'E'\n"

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

# define MAX_SIZE_MAP 500

typedef struct s_map
{
	int		width;
	int		height;
	char	*content;
}				t_map;

/*parse and check map*/
int	open_map(t_map *map);
int	check_map(t_map *map);
int	read_map(int fd, t_map *map);
int	check_size(t_map *map);
int	check_content_chars(t_map *map);
int	check_walls(t_map *map);
int	check_valid_path(t_map *map);
int	check_exit(char *map, int width);
int	color_cell(char *map, int cell);
int	color_adjacent_cells(char *map, int cell, int width, int height);
int	color_map_cells(char *map, int width, int height);
void	init_colored_map(char *map);
void	color_map(char *map, int width, int height);

/*display tiles*/
int display_tiles(t_map *map);

#endif