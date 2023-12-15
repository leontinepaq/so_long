
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

#define MALLOC_ERROR	1
#define	SIDE_LEN		1000

int	X = 50;
int Y = 50;

typedef struct s_img
{
	void	*img_ptr;
	char	*img_pixels_ptr;
	int		bits_per_pixel;
	int		endian;
	int		line_len;
	int		color;
}				t_img;

typedef struct	s_var
{
	void	*mlx;
	void	*win;
	t_img	img;
}				t_var;

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	int	offset;

	//🚨 Line len is in bytes. WIDTH 800 len_line ~3200 (can differ for alignment)
	offset = (img->line_len * y) + (x * (img->bits_per_pixel / 8));	

	*((unsigned int *)(offset + img->img_pixels_ptr)) = color;
}

void	color_screen(t_var *data, int color)
{
	for (int x = X; x < X + 10; ++x)
		for (int y = Y; y < Y + 10; ++y)	
		{
			my_pixel_put(&data->img, x, y, color);
		}
}

int	f(int keysym, t_var *data)
{

	if (keysym == XK_v) //violet
	{
		data->img.color = 0xba77ee;
		color_screen(data, data->img.color);
	}
	else if (keysym == XK_g) //green
	{
		data->img.color = 0xbef3a0;
		color_screen(data, data->img.color);
	}
	else if (keysym == XK_b) //blue
	{
		data->img.color = 0xa0e1f3;
		color_screen(data, data->img.color);
	}	
	else if (keysym == XK_Escape)
		exit(1);
	else if (keysym == XK_a)
	{
		color_screen(data, 0x000000);
		X-=10;
		color_screen(data, data->img.color);
	}
	else if (keysym == XK_d)
	{
		color_screen(data, 0x000000);
		X+=10;
		color_screen(data, data->img.color);
	}
	else if (keysym == XK_w)
	{
		color_screen(data, 0x000000);
		Y-=10;
		color_screen(data, data->img.color);
	}
	else if (keysym == XK_s)
	{
		color_screen(data, 0x000000);
		Y+=10;
		color_screen(data, data->img.color);
	}
	// push the READY image to window
	// the last parameters are the offset image-window
	mlx_put_image_to_window(data->mlx,
							data->win, 
							data->img.img_ptr, 
							0, 0);

	return 0;
}

int	main()
{
	t_var	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, SIDE_LEN, SIDE_LEN, "Test window");

	vars.img.img_ptr = mlx_new_image(vars.mlx,
									SIDE_LEN, 
									SIDE_LEN);
	vars.img.img_pixels_ptr = mlx_get_data_addr(vars.img.img_ptr, 
												&vars.img.bits_per_pixel, 
												&vars.img.line_len, 
												&vars.img.endian);
	//printf("Line_len %d <-> SIDE_LEN %d\nbpp %d\nendian %d\n", vars.img.line_len, SIDE_LEN, vars.img.bits_per_pixel, vars.img.endian);
	vars.img.color = 0xbef3a0;
	color_screen(&vars, vars.img.color);
	mlx_key_hook(vars.win, f, &vars);
	mlx_loop(vars.mlx);
}