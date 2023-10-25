NAME 		:= philo

SRCS		:= checker.c\
				clean.c\
				ft_lib.c\
				init.c\
				main.c\
				utils.c\

HEADER := philosopher.h

CC := cc
CC_FLAGS := -Wall -Wextra -Werror
RM := rm -f

OBJS := ${SRCS:.c=.o}

%.o : %.c	${HEADER}
	    ${CC} ${CC_FLAGS} -pthread -g -c $< -o $@

${NAME}:	${OBJS} ${LIBFT}
	 ${CC} ${CC_FLAGS} -o ${NAME} ${OBJS}

bonus:	${NAME_BONUS}

all:	${NAME}

clean:
	    ${RM} ${OBJS}

fclean:	clean
	    ${RM} ${NAME}

re:	    fclean all

.PHONY: all clean fclean re bonus
