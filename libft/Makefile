# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbastion <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/12 19:31:49 by vbastion          #+#    #+#              #
#    Updated: 2017/06/06 14:34:50 by vbastion         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libft.a
CC=gcc
CFLAGS=-Wall -Wextra -Werror

SRC=ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c \
	ft_memcmp.c ft_strlen.c ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strcat.c \
	ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strstr.c \
	ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c \
	ft_isalnum.c ft_isprint.c ft_isascii.c ft_toupper.c ft_tolower.c \
	ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c \
	ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c \
	ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_itoa.c ft_putchar.c \
	ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c \
	ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_pow.c ft_torad.c ft_todeg.c\
	ft_lstmerge.c ft_lstsize.c ft_lstat.c ft_lstfind.c ft_valid_base.c\
	ft_usage.c ft_abs.c ft_itoabase.c ft_atol.c ft_countbits.c  ft_activebits.c\
	ft_isspace.c ft_atoibase.c ft_atoinbase.c ft_atoihex.c get_next_line.c
OBJ=$(SRC:.c=.o)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)
	@echo "Built libft"

%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@

all: $(NAME)

clean:
	/bin/rm -f $(OBJ)
	@echo "Cleaned libft"

fclean: clean
	/bin/rm -f $(NAME)
	@echo "FCleaned libft"

re: fclean $(NAME)
