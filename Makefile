NAME = so_long

SRCS = test.c

OBJ_DIR = obj
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra

LIBFT_PATH		=	./libft
LIBFT			=	$(LIBFT_PATH)/libft.a

MLX_PATH		=	./MinilibX/minilibx-linux
MLX				=	$(MLX_PATH)/libmlx.a

$(OBJ_DIR)/%.o:	%.c
					$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(LIBFT) $(MLX) $(OBJ_DIR) $(OBJS)
			cp $(LIBFT) $(MLX) $(NAME)
			ar -rsc $(NAME) $(OBJS)

all: 	$(NAME)

$(LIBFT):
		make -C $(LIBFT_PATH) all

$(MLX):
		make -C $(MLX) all

$(OBJ_DIR):
		mkdir -p $(OBJ_DIR)

clean:	
		make -C $(LIBFT_PATH) clean
		make -C $(MLX_PATH) clean
		rm -rf $(OBJ_DIR)

fclean:	clean;
		make -C $(LIBFT_PATH) fclean
		make -C $(MLX_PATH) fclean
		rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re libft
