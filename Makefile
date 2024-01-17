NAME = so_long

SRCS = 	main.c init_functions.c \
		open_map.c check_map.c check_path.c check_path_color_map.c\
		open_window.c play_game.c move_player.c \
		render.c put_player.c put_background.c \
		put_images.c scale_image.c \
		put_moles.c animate_moles.c \
		animate_player.c animation_movements.c \
		free_functions.c close_game.c

OBJ_DIR = obj
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra -g3
MLXFLAGS = -lm -lbsd -lXext -lX11

LIBFT_PATH		=	./libft
LIBFT			=	$(LIBFT_PATH)/libft.a

MLX_PATH		=	./minilibx-linux
MLX				=	$(MLX_PATH)/libmlx.a

$(OBJ_DIR)/%.o:	%.c
					$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJ_DIR) $(OBJS) $(LIBFT) $(MLX)
			cp $(LIBFT) $(NAME)
			cp $(MLX) $(NAME)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX) $(MLXFLAGS)

all: 	$(LIBFT_PATH) $(MLX_PATH) $(NAME)

$(LIBFT):
		make -C $(LIBFT_PATH) all

$(MLX):
		make -C $(MLX_PATH) all

$(OBJ_DIR):
		mkdir -p $(OBJ_DIR)

clean:	
		make -C $(LIBFT_PATH) clean
		make -C $(MLX_PATH) clean
		rm -rf $(OBJ_DIR)

fclean:	clean;
		make -C $(LIBFT_PATH) fclean
		make -C $(MLX_PATH) clean
		rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re libft
