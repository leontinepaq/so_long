/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_images.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 23:11:47 by lpaquatt          #+#    #+#             */
/*   Updated: 2024/01/26 16:50:13 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

unsigned int	find_color_pixel(t_img *img, int x, int y)
{
	char	*color;
	int		offset;

	offset = (img->line_len * y) + (x * (img->bits_per_pixel / 8));
	color = img->img_pixels_ptr + offset;
	return (*((unsigned int *)color));
}

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	int	offset;

	if ((unsigned int) color == 0xFF000000)
		return ;
	offset = (img->line_len * y) + (x * (img->bits_per_pixel / 8));
	if (offset < (img->line_len * img->height)
		+ (img->width * (img->bits_per_pixel / 8))
		&& offset >= 0)
		*((unsigned int *)(offset + img->img_pixels_ptr)) = color;
}

void	overlap_image(t_var *vars, t_img *src, int pos_x, int pos_y)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < src->height)
	{
		x = 0;
		while (x < src->width)
		{
			color = find_color_pixel(src, x, y);
			my_pixel_put(vars->img, x + pos_x, y + pos_y, color);
			x++;
		}
		y++;
	}
}

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

t_img	*file_to_image(t_var *vars, char *path)
{
	t_img	*img;
	int		img_width;
	int		img_height;

	img = malloc(sizeof(t_img));
	if (!img)
		return (ft_printf(ERROR_MALLOC), NULL);
	img->img_ptr = mlx_xpm_file_to_image(vars->mlx, path,
			&img_width, &img_height);
	if (!img->img_ptr)
		return (ft_printf(ERROR_MLX), ft_printf("Reading file : %s\n", path),
			free(img), NULL);
	img->height = img_height;
	img->width = img_width;
	img->img_pixels_ptr = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel,
			&img->line_len, &img->endian);
	img = scale_img(vars, img);
	if (!img)
		return (ft_printf("Reading file : %s\n", path), NULL);
	return (img);
}
