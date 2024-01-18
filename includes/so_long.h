/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 01:06:01 by lpaquatt          #+#    #+#             */
/*   Updated: 2024/01/18 22:39:34 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <sys/time.h>
# include <math.h>

# define ERROR_MALLOC "Error\nProblem with memory allocation (malloc function)\n"
# define ERROR_MLX "Error\nSomething went wrong using a minilibx function\n"
# define ERROR_MAP_MESS "Error\nProblem with the configuration of the map : "
# define ERROR_MAP_RECT "Map is not rectangular\n"
# define ERROR_MAP_UNKNOWN "Unknown character\n"
# define ERROR_MAP_WALLS "Map must be closed by walls\n"
# define ERROR_MAP_PATH "No valid path found\n"
# define ERROR_MAP_CONTAINS "Must have 1 'P', at least 1 'C' and 1 'E'\n"
# define ERROR_MAP_OBJS "Objects ('C', 'P', 'M' and 'E') must be on the ground\n"

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

# define MAX_SIZE_MAP 500
# define TILE_SIZE 32
# define SPRITE_SIZE 32
# define OVERLAP_SIZE 5
# define DELAY 1000

# define NORMAL 0
# define WALK 2
# define JUMP 5
# define FALL 6
# define DEATH 8

# define POS_CENTER 0
# define POS_UP 1
# define POS_LEFT 2
# define POS_RIGHT 3

# define DIR_DOWN 0
# define DIR_UP 1
# define DIR_LEFT 2
# define DIR_RIGHT 3

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
}	t_img;

typedef struct s_map
{
	int		width;
	int		height;
	char	*content;
	char	**tiles;
}	t_map;

typedef struct s_position
{
	int	x_tile;
	int	y_tile;
	int	pos_on_tile;
}	t_pos;

typedef struct s_anim
{
	time_t	timestamp;
	int		movement;
	t_pos	*position;
	int		direction;
	int		anim_frame;
}	t_anim;

typedef struct s_game
{
	t_anim	*player;
	int		collectibles;
	int		moves;
	char	*nb_moves;
	int		end_of_game;
}	t_game;

typedef struct s_assets
{
	t_img	*collectible;
	t_img	*exit_close;
	t_img	*exit_open;
	t_img	*player;
	t_img	*tile_ground;
	t_img	*tile_wall;
	t_img	*background_1;
	t_img	*background_2;
	t_img	*background_3;
	t_img	*victory;
	t_img	*game_over;
	t_img	*mole;
}	t_assets;

typedef struct s_var
{
	void		*mlx;
	void		*win;
	t_map		*map;
	t_game		*game;
	t_img		*img;
	int			scale;
	t_assets	*assets;
}	t_var;

/*init_functions*/
t_var			*malloc_vars(void);
void			find_special_items(t_var *vars);
int				init_game(t_var *vars);

/*open map*/
int				read_map(int fd, t_map *map);
int				check_map(t_map *map);
int				malloc_tiles(t_map *maP);
int				create_tiles(t_map *map);
int				open_map(t_map *map);

/*check map*/
int				check_size(t_map *map);
int				check_content_chars(t_map *map);
int				check_walls(t_map *map);
int				check_objects(t_map *map);

/*check path*/
int				check_exit(char *map, int width);
int				check_valid_path(t_map *map);

/*check path - color map*/
int				color_cell(char *map, int cell);
int				color_adjacent_cells(char *map, int cell, int width,
					int height);
int				color_map_cells(char *map, int width, int height);
void			init_colored_map(char *map);
void			color_map(char *map, int width, int height);

/*open window*/
int				open_asset(t_var *vars, t_img **asset, char *path);
int				open_assets(t_var *vars);
int				open_img(t_var *vars);
int				open_window(t_var *vars);

/*move player.c*/
void			update_player_on_x(t_var *vars, int move_x);
void			update_player_on_y(t_var *vars, int move_y);
int				update_nb_moves(t_var *vars);
int				player_is_moving(t_var *vars, int move_x, int move_y);
int				move_player(t_var *vars, int move_x, int move_y);

/*move on tiles*/
void			collect_collectibles(t_var *vars);
void			move_on_tiles(t_var *vars, int move_x, int move_y);

/*play game*/
void			open_exit(t_var *vars);
void			display_victory(t_var *vars, int move_x, int move_y);
int				manage_keys(int keysym, t_var *vars);

/*render*/
void			put_specific_tile(int x, int y, t_var *vars);
void			put_tiles(t_var *vars);
void			put_nb_moves(t_var *vars);
int				render(t_var *vars);

/*put background*/
void			put_layer_background(t_var *vars, t_img *background);
void			put_background(t_var *vars);

/*put moles*/
void			animate_mole(int x, int y, int *row, int *col);
int				put_one_mole(t_var *vars, int x, int y);
int				put_moles(t_var *vars);

/*put player*/
t_img			*create_transp_sprite(t_var *vars);
t_img			*crop_sprite(t_img *sheet, t_var *vars, int row, int col);
void			find_coordinates(int *x_ptr, int *y_ptr,
					t_var *vars, t_pos *position);
int				put_player(t_var *vars);

/*animate player*/
int				is_player_on_ground(t_var *vars);
void			first_animation(t_var *vars, t_anim *player,
					time_t current_timestamp);
void			play_movement_animation(t_var *vars);
void			animate_player(t_var *vars);

/*animation movements*/
void			animate_normal(t_var *vars, t_anim *player);
void			animate_walk_left(t_var *vars, t_anim *player);
void			animate_walk_right(t_var *vars, t_anim *player);
void			animate_jump(t_var *vars, t_anim *player);
void			animate_fall(t_var *vars, t_anim *player);

/*put images*/
unsigned int	find_color_pixel(t_img *img, int x, int y);
void			my_pixel_put(t_img *img, int x, int y, int color);
void			overlap_image(t_var *vars, t_img *src, int pos_x, int pos_y);
void			make_transparent(t_img *img);
t_img			*file_to_image(t_var *vars, char *path);

/*scale image*/
void			copy_img_scaled(t_img *scaled_img, t_img	*img);
t_img			*scale_img(t_var *vars, t_img *img);

/*free functions*/
void			free_tiles(t_map *map);
void			free_one_asset(void *mlx, t_img *asset);
void			free_assets(t_var *vars);
void			free_vars(t_var *vars);

/*close game*/
void			check_game_over(t_var *vars);
void			display_end_of_game(t_var *vars);
void			close_window(t_var *vars);
int				closure(t_var *vars);

#endif