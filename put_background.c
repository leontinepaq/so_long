/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_background.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 18:44:42 by lpaquatt          #+#    #+#             */
/*   Updated: 2023/12/27 18:45:21 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

int	put_layer_background(t_var *vars, char *path)
{
	t_img	*background;
	int		i;
	int		j;

	i = 0;
	background = file_to_image(vars, path);
	if (!background)
		return (EXIT_FAILURE);
	while (i * background->width < vars->img->width)
	{
		j = 0;
		while (j * background->height < vars->img->height)
		{
			overlap_image(vars, background, i * background->width,
				j * background->height);
			j++;
		}
		i++;
	}
	mlx_destroy_image(vars->mlx, background->img_ptr);
	free(background);
	return (EXIT_SUCCESS);
}

int	put_background(t_var *vars)
{
	if (put_layer_background(vars, "designs/Rock1.xpm") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (put_layer_background(vars, "designs/Rock2.xpm") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (put_layer_background(vars, "designs/Rock3.xpm") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
