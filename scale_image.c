/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:34:37 by lpaquatt          #+#    #+#             */
/*   Updated: 2024/01/26 17:00:00 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

void	copy_img_scaled(t_img *scaled_img, t_img	*img)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			color = find_color_pixel(img, x, y);
			my_pixel_put(scaled_img, 2 * x, 2 * y, color);
			my_pixel_put(scaled_img, 2 * x + 1, 2 * y, color);
			my_pixel_put(scaled_img, 2 * x, 2 * y + 1, color);
			my_pixel_put(scaled_img, 2 * x + 1, 2 * y + 1, color);
			x++;
		}
		y++;
	}
}

t_img	*scale_img(t_var *vars, t_img *img)
{
	t_img	*scaled_img;

	if (vars->scale != 2)
		return (img);
	scaled_img = malloc(sizeof(t_img));
	if (!scaled_img)
		return (mlx_destroy_image(vars->mlx, img->img_ptr), free(img),
			ft_printf(ERROR_MALLOC), NULL);
	scaled_img->width = img->width * vars->scale;
	scaled_img->height = img->height * vars->scale;
	scaled_img->img_ptr = mlx_new_image(vars->mlx, scaled_img->width,
			scaled_img->height);
	if (!scaled_img->img_ptr)
		return (mlx_destroy_image(vars->mlx, img->img_ptr), free(img),
			free(scaled_img), ft_printf(ERROR_MLX), NULL);
	scaled_img->img_pixels_ptr = mlx_get_data_addr(scaled_img->img_ptr,
			&scaled_img->bits_per_pixel,
			&scaled_img->line_len, &scaled_img->endian);
	if (!scaled_img->img_pixels_ptr)
		return (mlx_destroy_image(vars->mlx, img->img_ptr), free(img),
			mlx_destroy_image(vars->mlx, scaled_img->img_ptr), free(scaled_img),
			ft_printf(ERROR_MLX), NULL);
	make_transparent(scaled_img);
	copy_img_scaled(scaled_img, img);
	return (mlx_destroy_image(vars->mlx, img->img_ptr), free(img), scaled_img);
}
