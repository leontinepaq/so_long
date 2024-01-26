/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 14:33:43 by lpaquatt          #+#    #+#             */
/*   Updated: 2024/01/26 16:28:30 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

t_img	*create_transp_sprite(t_var *vars)
{
	t_img	*sprite;

	sprite = malloc(sizeof(t_img));
	if (!sprite)
		return (ft_printf(ERROR_MALLOC), NULL);
	sprite->width = SPRITE_SIZE * vars->scale;
	sprite->height = SPRITE_SIZE * vars->scale;
	sprite->img_ptr = mlx_new_image(vars->mlx, sprite->width, sprite->height);
	if (!sprite->img_ptr)
		return (free(sprite), ft_printf(ERROR_MLX), NULL);
	sprite->img_pixels_ptr = mlx_get_data_addr(sprite->img_ptr,
			&sprite->bits_per_pixel,
			&sprite->line_len, &sprite->endian);
	if (!sprite->img_pixels_ptr)
		return (mlx_destroy_image(vars->mlx, sprite->img_ptr),
			free(sprite), ft_printf(ERROR_MLX), NULL);
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
			color = find_color_pixel(sheet, col * sprite->width + x,
					row * sprite->height + y);
			my_pixel_put(sprite, x, y, color);
			x++;
		}
		y++;
	}
	return (sprite);
}

void	find_coordinates(int *x_ptr, int *y_ptr, t_var *vars, t_pos *position)
{
	*x_ptr = ((position->x_tile * TILE_SIZE)
			+ (TILE_SIZE - SPRITE_SIZE) / 2) * vars->scale;
	*y_ptr = ((position->y_tile * TILE_SIZE)
			+ (TILE_SIZE - SPRITE_SIZE)) * vars->scale;
	if (position->pos_on_tile == POS_UP)
		*y_ptr -= TILE_SIZE / 2 * vars->scale;
	else if (position->pos_on_tile == POS_RIGHT)
		*x_ptr += TILE_SIZE / 3 * vars->scale;
	else if (position->pos_on_tile == POS_LEFT)
		*x_ptr -= TILE_SIZE / 3 * vars->scale;
}

int	put_player(t_var *vars)
{
	t_img	*player;
	int		x;
	int		y;

	player = crop_sprite(vars->assets->player, vars,
			vars->game->player->movement, vars->game->player->anim_frame);
	if (!player)
		return (EXIT_FAILURE);
	find_coordinates(&x, &y, vars, vars->game->player->position);
	overlap_image(vars, player, x, y);
	mlx_destroy_image(vars->mlx, player->img_ptr);
	free(player);
	return (EXIT_SUCCESS);
}
