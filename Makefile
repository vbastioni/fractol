CC=gcc
CFLAGS=-Wall -Wextra -Werror
NAME=fractol
FT=./libft
MLX=./minilibx_macos
LIBS=-I ./includes -I ${FT}
CLIBS=-L${FT} -lft -framework OpenGL -framework AppKit
LIBS+=-I ${MLX}
CLIBS+=-L ${MLX}
CLIBS+=-lmlx

ITEM:=\
	callback.o\
	color.o\
	complex.o\
	draw.o\
	tree.o\
	img.o\
	main.o\
	newton.o\
	sponge.o\
	utils.o
OBJ:=$(addprefix ./src/, $(ITEM))

$(NAME): $(OBJ)
	@make -C $(MLX)
	@make -C $(FT)
	@$(CC) $(OBJ) $(CFLAGS) -o $@ ${CLIBS}
	@echo "Compiled fractol."

%.o: %.c
	@$(CC) $(CFLAGS) -c $? ${LIBS} -o $@

all: ${NAME}

clean:
	@rm -rf ${OBJ}
	@make -C ${FT} clean
	@make -C ${MLX} clean
	@echo "Cleaned Fractol"

fclean: clean
	@rm -f ${NAME}
	@make -C ${FT} fclean
	@echo "FCleaned Fractol"

re: fclean all
