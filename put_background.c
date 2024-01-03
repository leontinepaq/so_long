/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_background.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 18:44:42 by lpaquatt          #+#    #+#             */
/*   Updated: 2024/01/02 14:11:03 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

int	put_layer_background(t_var *vars, t_img *background)
{
	int		i;
	int		j;

	i = 0;
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
	return (EXIT_SUCCESS);
}

int	put_background(t_var *vars)
{
	if (put_layer_background(vars, vars->assets->background_1) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (put_layer_background(vars, vars->assets->background_2) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (put_layer_background(vars, vars->assets->background_3) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
