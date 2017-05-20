CC=gcc
CFLAGS=-Wall -Wextra -Werror
NAME=fractol
FT=./libft
MLX=./minilibx_macos
LIBS=-I ./includes -I ${FT}
CLIBS=-L${FT} -lft -framework OpenGL -framework AppKit
ifeq ("${VERSION}", "2015")
LIBS+=-I ${MLX}
CLIBS+=-L ${MLX}
else
	ifeq ("${VERSION}", "2017")
		LIBS+=-I ${MLX}
		CLIBS+=-L ${MLX}
	endif
endif
CLIBS+=-lmlx

OBJ:=\
	color.o\
	draw.o\
	main.o

$(NAME): $(OBJ)
	make -C $(MLX)
	make -C $(FT)
	$(CC) $? $(CFLAGS) -o $@ ${CLIBS}

%.o: %.c
	$(CC) $(CFLAGS) -c $? ${LIBS}

${MLX}:
	make -C ${MLX}

${FT}:
	make -C ${FT}

all: ${NAME}

clean:
	rm -rf ${OBJ}

fclean: clean
	rm -f ${NAME}

re: fclean all
