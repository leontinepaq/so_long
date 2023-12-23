/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 01:06:01 by lpaquatt          #+#    #+#             */
/*   Updated: 2023/12/23 00:26:13 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <X11/keysym.h>
# include <X11/X.h>

# define ERROR_MALLOC "Error malloc\n"
# define ERROR_MLX "Error MLX\n"
# define ERROR_MAP_MESS "Error\nProblem with the configuration of the map : "
# define ERROR_MAP_RECT "Map is not rectangular\n"
# define ERROR_MAP_UNKNOWN "Unknown character\n"
# define ERROR_MAP_WALLS "Map must be closed by walls\n"
# define ERROR_MAP_PATH "No valid path found\n"
# define ERROR_MAP_CONTAINS "Must have 1 'P', at least 1 'C' and 1 'E'\n"

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

# define MAX_SIZE_MAP 500
# define TILE_SIZE 32
# define OVERLAP_SIZE 5


typedef struct s_map
{
	int		width;
	int		height;
	char	*content;
	char	**tiles;
}				t_map;


typedef struct s_img
{
	void	*img_ptr;
	char	*img_pixels_ptr;
	int		bits_per_pixel;
	int		endian;
	int		line_len;
	char	*address;
	int		width;
	int		height;
}				t_img;

typedef struct	s_var
{
	void	*mlx;
	void	*win;
	t_map	*map;
	t_img	*img;
}				t_var;

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
int display_tiles(t_map *map, t_var *vars);

/*render*/
int	put_layer_background(t_var *vars, char *path);
int	put_background(t_var *vars);
int	render(t_var *vars);

/*put images*/
unsigned int	find_color_pixel(t_img *img, int x, int y);
void	my_pixel_put(t_img *img, int x, int y, int color);
void	overlap_image(t_var *vars, t_img *src, int pos_x, int pos_y);
t_img	*file_to_image(t_var *vars, char *path);

/*closing game*/
void	free_tiles(t_map *map);
void	free_map(t_map *map);
int	escape(int keysym, t_var *vars);
int	close_window(t_var *vars);
int	closure(t_var *vars);

#endif