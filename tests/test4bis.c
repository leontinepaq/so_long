
/*
Point qui se deplace dans la fenetre :
- asdw pour le deplacement
- gvb pour changer la couleur
*/



#include "includes/so_long.h"

#include "minilibx-linux/mlx.h"
#include <X11/keysym.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE_TILE	10
#define	SIDE_LEN	1000

int	X = 50;
int Y = 50;

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	int	offset;

	offset = (img->line_len * y) + (x * (img->bits_per_pixel / 8));	
	*((unsigned int *)(offset + img->img_pixels_ptr)) = color;

}

void	put_img(t_var *data, int color)
{
	for (int x = 0; x < SIZE_TILE; ++x)
		for (int y = 0; y < SIZE_TILE; ++y)	
		{
			my_pixel_put(&data->img, x, y, color);
		}
}

int	f(int keysym, t_var *data)
{
	if (keysym == XK_v) //violet
	{
		put_img(data, 0xba77ee);
	}
	else if (keysym == XK_g) //green
	{
		put_img(data, 0xbef3a0);
	}
	else if (keysym == XK_b) //blue
	{
		put_img(data, 0xa0e1f3);
	}	
	else if (keysym == XK_a || keysym == XK_Left)
	{
		X-=10;
	}
	else if (keysym == XK_d || keysym == XK_Right)
	{
		X+=10;
	}
	else if (keysym == XK_w || keysym == XK_Up)
	{
		Y-=10;
	}
	else if (keysym == XK_s || keysym == XK_Down)
	{
		Y+=10;
	}
	else if (keysym == XK_Escape)
		exit(1);
	// push the READY image to window
	// the last parameters are the offset image-window
	mlx_put_image_to_window(data->mlx,
							data->win, 
							data->img->img_ptr, 
							X, Y);

	return 0;
}

int	escape(int keysym, t_var *vars)
{
	if (keysym == XK_Escape)
	{
        mlx_destroy_window(vars->mlx, vars->win);
        vars->win = NULL;
	}
	return (EXIT_SUCCESS);
}


int	closure(t_var *application)
{
	mlx_destroy_window(application->mlx, application->win);
	exit(0);
	return (1);
}
#include <X11/X.h>
int	main()
{
	t_var	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, SIDE_LEN, SIDE_LEN, "Test window");

	vars.img.img_ptr = mlx_new_image(vars.mlx, SIZE_TILE, SIZE_TILE);
	vars.img.img_pixels_ptr = mlx_get_data_addr(vars.img.img_ptr, &vars.img.bits_per_pixel, &vars.img.line_len,&vars.img.endian);
	put_img(&vars, 0xbef3a0);
	//mlx_key_hook(vars.win, f, &vars);
	mlx_hook(vars.win, KeyPress, KeyPressMask, &f, &vars);
	mlx_hook(vars.win, ClientMessage, NoEventMask, closure, &vars);
	mlx_loop(vars.mlx);
}
