# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/22 12:21:57 by jmatute-          #+#    #+#              #
#    Updated: 2021/10/16 18:07:29 by jmatute-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= utils.c pipex.c

LIBFT_DIR	= libft/

OBJS	= ${SRCS:.c=.o}

NAME	= pipex

CC		= gcc
RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror #-fsanitize=address

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${SRCS} pipex.h Makefile
			@make -sC ${LIBFT_DIR}
			@cp ./libft/libft.a .
			${CC} ${CFLAGS} ${SRCS} libft.a -o ${NAME}

all:		${NAME}

clean:
			@make -sC ${LIBFT_DIR} clean
			${RM} ${OBJS} libft.a

fclean:		clean
			@make -sC ${LIBFT_DIR} fclean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re