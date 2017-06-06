CC=gcc
CFLAGS=-Wall -Wextra -Werror
NAME=fractol
FT:=./libft
MLX=./minilibx_macos
LIBS=-I ./includes -I ${FT}
CLIBS=-L${FT} -lft -framework OpenGL -framework AppKit
LIBS+=-I ${MLX}
CLIBS+=-L ${MLX}
CLIBS+=-lmlx
MDIR=mkdir -p obj

#.SILENT:

ITEM:=\
	callback.o\
	color.o\
	complex.o\
	env_setter.o\
	gradient.o\
	handler.o\
	img.o\
	main.o\
	mandel.o\
	newton.o\
	qe_event.o\
	sponge.o\
	threading.o\
	tree.o\
	triangle.o\
	utils.o\
	util_math.o
OBJ:=$(addprefix obj/, $(ITEM))


$(NAME): $(OBJ)
	@make -C ${FT}
	@make -C ${MLX}
	$(CC) $(CFLAGS) -O3 $(OBJ) -o $@ ${CLIBS} -fsanitize=address
	@echo "Compiled fractol."

$(FT):
	@make -C $?

$(MLX):
	@make -C $?

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -O3 -c $? ${LIBS} -o $@ 

all: ${NAME}

clean:
	rm -rf ${OBJ}
	@make -C ${FT} clean
	@make -C ${MLX} clean
	@echo "Cleaned Fractol"

fclean: clean
	rm -f ${NAME}
	@make -C ${FT} fclean
	@echo "FCleaned Fractol"

re: fclean all
