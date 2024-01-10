/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_background.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 18:44:42 by lpaquatt          #+#    #+#             */
/*   Updated: 2024/01/09 13:44:36 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

void	put_layer_background(t_var *vars, t_img *background)
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
}

void	put_background(t_var *vars)
{
	put_layer_background(vars, vars->assets->background_1);
	put_layer_background(vars, vars->assets->background_2);
	put_layer_background(vars, vars->assets->background_3);
}
