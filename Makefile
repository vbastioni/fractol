# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbastion <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/21 14:44:05 by vbastion          #+#    #+#              #
#    Updated: 2017/06/21 15:33:01 by vbastion         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS=-Wall -Wextra -Werror -O2
NAME=fractol
FT:=./libft
LFT:=libft.a
FLFT:=${FT}/${LFT}
MLX=./minilibx_macos
LMLX:=libmlx.a
FLMLX:=${MLX}/${LMLX}
OBJ_D:=obj/
SRC_D:=src/
LIBS=-I./src -I ${FT} -I ${MLX}
CLIBS=${FT}/$(LFT) $(MLX)/$(LMLX) -framework OpenGL -framework AppKit -lm
MDIR=mkdir -p obj
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
OBJ:=$(addprefix $(OBJ_D), $(ITEM))
HEADERS:=$(SRC_D)/fractol.h

#.SILENT:

all: build

build:
	$(MAKE) $(NAME)

$(NAME): $(FLFT) $(FLMLX) $(OBJ)
	@printf "\033[32mBUILDING $@\033[0m\n"
	$(CC) $(CFLAGS) $(CLIBS) $(OBJ) -o $@
	@printf "\033[32mDONE BUILDING $@\033[0m\n"

$(OBJ_D)%.o: $(SRC_D)%.c $(HEADERS) ${FLFT} ${FLMLX}
	mkdir -p $(OBJ_D)
	$(CC) $(CFLAGS) $(LIBS) -c $< -o $@

$(FLMLX):
	$(MAKE) -C $(MLX)

$(FLFT):
	$(MAKE) -C $(FT)

clean:
	/bin/rm -f $(OBJ)
	$(MAKE) -C ${FT} clean
	$(MAKE) -C ${MLX} clean
	echo "Cleaned Fractol"

fclean: clean
	rm -f ${NAME}
	$(MAKE) -C ${FT} fclean
	echo "FCleaned Fractol"

re: fclean all

.PHONY: re fclean clean all 
