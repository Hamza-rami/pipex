NAME = pipex

SRC = mandatory/ft_splite.c mandatory/ft_strjoin.c mandatory/get_envvp.c mandatory/pipex.c

INC = pipex.h
OBJS = ${SRC:.c=.o}
CC = cc -Wall -Wextra -Werror -fsanitize=address -g3
RM = rm -rf

%.o: %.c ${INC}
	${CC} -c $< -o $@

${NAME}:${OBJS}
	${CC} ${OBJS} -o ${NAME}

all: ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME} 

re: fclean all