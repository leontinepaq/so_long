/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 14:33:43 by lpaquatt          #+#    #+#             */
/*   Updated: 2024/01/02 13:36:02 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

void	make_transparent(t_img *img)
{
	int	offset;

	offset = 0;
	while (offset < (img->line_len * img->height)
		+ (img->width * (img->bits_per_pixel / 8))
		&& offset >= 0)
	{
		*((unsigned int *)(offset + img->img_pixels_ptr)) = 0xFF000000;
		offset += img->bits_per_pixel / 8;
	}
}

t_img	*create_transp_sprite(t_var *vars)
{
	t_img	*sprite;

	sprite = malloc(sizeof(t_img));
	if (!sprite)
		return (ft_printf(ERROR_MALLOC), NULL);
	sprite->width = SPRITE_SIZE;
	sprite->height = SPRITE_SIZE;
	sprite->img_ptr = mlx_new_image(vars->mlx, SPRITE_SIZE, SPRITE_SIZE);
	if (!sprite->img_ptr)
		return (ft_printf(ERROR_MLX), NULL);
	sprite->img_pixels_ptr = mlx_get_data_addr(sprite->img_ptr,
			&sprite->bits_per_pixel,
			&sprite->line_len, &sprite->endian);
	make_transparent(sprite);
	return (sprite);
}

t_img	*crop_sprite(t_img *sheet, t_var *vars, int row, int col)
{
	t_img	*sprite;
	int		x;
	int		y;
	int		color;

	sprite = create_transp_sprite(vars);
	if (!sprite)
		return (NULL);
	y = 0;
	while (y < sprite->height)
	{
		x = 0;
		while (x < sprite->width)
		{
			color = find_color_pixel(sheet, col * SPRITE_SIZE + x,
					row * SPRITE_SIZE + y);
			my_pixel_put(sprite, x, y, color);
			x++;
		}
		y++;
	}
	return (sprite);
}

void	animate_player(t_game *game)
{
    struct 			timeval te;
	unsigned int	milliseconds;
	
    gettimeofday(&te, NULL); // get current time
    milliseconds = (unsigned int)(te.tv_sec*1000LL + te.tv_usec/1000) % DELAY;
	if (game->move_player == NORMAL)
	{
		if (milliseconds < DELAY / 2)
			game->anim_player = 0;
		else game->anim_player = 1;
	}
	if (game->move_player == WALK)
	{
		if ((milliseconds + DELAY - game->time_anim) % DELAY < DELAY / 4)
		{
			game->anim_player = 0;
		}	
		else if ((milliseconds + DELAY - game->time_anim) % DELAY < 2 * DELAY / 4)
		{
			game->anim_player = 1;
		}
		else if ((milliseconds + DELAY - game->time_anim) % DELAY < 3 * DELAY / 4)
		{
			game->anim_player = 2;
		}
		else 
			{
				game->anim_player = 3;
				game->move_player = NORMAL;
			}
	}
}

int	put_player(t_var *vars)
{
	t_img	*player_sheet;
	t_img	*player;
	int		x;
	int		y;

	animate_player(vars->game);
	x = vars->game->x_player;
	y = vars->game->y_player;
	player_sheet = file_to_image(vars, "designs/AnimationSheet_Character.xpm");
	if (!player_sheet)
		return (EXIT_FAILURE);
	player = crop_sprite(player_sheet, vars, 
		vars->game->move_player, vars->game->anim_player);
	if (!player)
		return (EXIT_FAILURE);
	overlap_image(vars, player, x * (TILE_SIZE) + (TILE_SIZE - SPRITE_SIZE) / 2,
		(y * TILE_SIZE) + (TILE_SIZE - SPRITE_SIZE));
	mlx_destroy_image(vars->mlx, player->img_ptr);
	mlx_destroy_image(vars->mlx, player_sheet->img_ptr);
	free(player_sheet);
	free(player);
	return (EXIT_SUCCESS);
}
