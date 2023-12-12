/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaquatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:06:31 by lpaquatt          #+#    #+#             */
/*   Updated: 2023/12/12 18:08:53 by lpaquatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*https://github.com/suspectedoceano/mlx/blob/main/mlx_explained*/

#include "includes/so_long.h"

#include <X11/X.h>
#include <stdio.h>

#define MALLOC_ERROR 1
#define WIN_WIDTH 1000
#define WIN_HEIGHT 1000


typedef struct  s_data
{
    void        *mlx_ptr;
    void        *win_ptr;
	int         color;
}               t_data;

int     button_press(int button, int x, int y, t_data *data)
{
    (void) data;
	if (button == 1)
        printf("Left mouse button pressed at (%d, %d)!\n", x, y);
    else if (button == 3)
        printf("Right mouse button pressed at (%d, %d)!\n", x, y);

    return (0);
}

int f(int keysym, t_data *data)
{
    (void) data;
	printf("Pressed %d\n", keysym); //sleep to appreciate loop_hook stopping
    sleep(5);
    return 1;
}
int	change_color (t_data *data)
{
	mlx_string_put(data->mlx_ptr, data->win_ptr, 400, 400, data->color,"Colour changing text");

	if (data->color == 0xCCF5AC)
		data->color = 0x9bbe74;
	else if (data->color == 0x9bbe74)
		data->color = 0x808a9f;
	else if (data->color == 0x808a9f)
		data->color = 0x2c497f;
	else if (data->color == 0x2c497f)
		data->color = 0x3d2b56;
	else data->color = 0xCCF5AC;
	sleep(1);
	return (0);
}


int main()
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (MALLOC_ERROR);

	data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Test window");
	data.color = 0xCCF5AC;
	if (!data.win_ptr)
	{ 
		mlx_destroy_display(data.mlx_ptr);
		free (data.mlx_ptr);
		return (MALLOC_ERROR);
	}
	
	mlx_key_hook(data.win_ptr, f, &data);
	mlx_loop_hook(data.mlx_ptr, change_color, &data);
	
	mlx_loop(data.mlx_ptr);
	
	mlx_destroy_window(data.mlx_ptr,data.win_ptr);
	mlx_destroy_display(data.mlx_ptr);
	free (data.mlx_ptr);
	return (0);
}
