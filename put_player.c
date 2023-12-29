/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 14:33:43 by lpaquatt          #+#    #+#             */
/*   Updated: 2023/12/29 14:01:43 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

#define SPRITE_SIZE 32
#define NORMAL 0
#define WALK 1
#define JUMP 2

void	make_transparent(t_img *img)
{
	int offset;

	offset = 0;
	while (offset < (img->line_len * img->height)
		+ (img->width * (img->bits_per_pixel / 8))
		&& offset >= 0)
	{
		*((unsigned int *)(offset + img->img_pixels_ptr)) = 0xFF000000;
		offset += img->bits_per_pixel / 8;
	}
}

t_img	*crop_sprite(t_img *sheet, t_var *vars, int row, int col)
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
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < sprite->height)
	{
		x = 0;
		while (x < sprite->width)
		{
			color = find_color_pixel(sheet, row * SPRITE_SIZE + x, col * SPRITE_SIZE + y);
			my_pixel_put(sprite, x, y, color);
			x++;
		}
		y++;
	}
	return (sprite);
}


int	put_player(t_var *vars)
{
	t_img	*player_sheet;
	t_img	*player;
	int		x;
	int		y;

	x = vars->game->x_player;
	y = vars->game->y_player;
	player_sheet = file_to_image(vars, "designs/AnimationSheet_Character.xpm");
	if (!player_sheet)
		return (EXIT_FAILURE);
	player = crop_sprite(player_sheet, vars, 0, 0);
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
