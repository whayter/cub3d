NAME = Cub3D

CC = gcc

MKD = mkdir

RM = rm -rf

SRCS = 	./sources/main.c				\
		./sources/check_file.c			\
		./sources/get_info.c			\
		./sources/initialization.c		\
		./sources/initialization_2.c	\
		./sources/initialization_3.c	\
		./sources/get_map.c				\
		./sources/parse_map.c			\
		./sources/raycasting.c			\
		./sources/keys.c				\
		./sources/motion.c				\
		./sources/floors.c				\
		./sources/sprites.c				\
		./sources/textures.c			\
		./sources/player.c				\
		./sources/shoot.c				\
		./sources/save.c				\
		./sources/exit.c				\

OBJ = $(SRCS:%.c=%.o)

IFLAGS = ./includes/

CFLAGS = -g -Wall -Wextra -Werror -lm -lbsd -lX11 -lXext

SRC_DIR = sources

MLX_DIR = mlx

LIB_DIR = libft

NAMELIB = libft.a

NAMEMLX = libmlx.a

STRT_STYLE = \033[1;32m

END_STYLE = \033[0m

all: $(NAME)

%.o: %.c
	@(gcc $(CFLAGS) -c -I$(IFLAGS) -I$(MLX_DIR) -I$(LIB_DIR) $< -o $(<:.c=.o))

$(NAME): $(OBJ)
	@(echo "$(STRT_STYLE)Compiling...$(END_STYLE)")
	@(cd $(LIB_DIR) && make -s)
	@(cd $(MLX_DIR) && make -s)
	@(gcc -o $(NAME) -I$(IFLAGS) -I$(MLX_DIR) $(OBJ) $(MLX_DIR)/$(NAMEMLX) $(LIB_DIR)/$(NAMELIB) $(MLX_DIR)/libmlx_Linux.a $(CFLAGS))
	@(echo "$(STRT_STYLE)Done.$(END_STYLE)")

clean:
	@(echo "$(STRT_STYLE)Cleaning...$(END_STYLE)")
	@(make -s clean -C $(LIB_DIR))
	@(make -s clean -C $(MLX_DIR))
	@($(RM) $(SRC_DIR)/*.o)
	@(echo "$(STRT_STYLE)Done.$(END_STYLE)")

fclean: clean
	@(echo "$(STRT_STYLE)Fcleaning...$(END_STYLE)")
	@(make -s fclean -C $(LIB_DIR))
	@($(RM) $(NAME))
	@(echo "$(STRT_STYLE)Done.$(END_STYLE)")

re: fclean all

.PHONY: all clean fclean re