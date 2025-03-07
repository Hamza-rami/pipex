NAME = pipex
NAME_BNS = pipex_b

SRC = mandatory/ft_splite.c mandatory/ft_strjoin.c mandatory/get_envvp.c mandatory/pipex.c mandatory/get_paths.c
SRC_BNS = bonus/ft_splite_bonus.c bonus/ft_string.c bonus/get_envvp_bonus.c bonus/get_next_line_utils.c bonus/get_next_line.c \
			bonus/help_main.c bonus/here_doc.c bonus/pipex_bonus.c 

INC = mandatory/pipex.h
INC_BNS = bonus/pipex_bonus.h
OBJS = ${SRC:.c=.o}
OBJS_BNS = ${SRC_BNS:.c=.o}
CC = cc -Wall -Wextra -Werror 
RM = rm -rf

all: ${NAME}

mandatory/%.o: mandatory/%.c ${INC}
	${CC} -c $< -o $@

bonus/%.o: bonus/%.c ${INC_BNS}
	${CC} -c $< -o $@

${NAME}:${OBJS}
	${CC} ${OBJS} -o ${NAME}

bonus:  ${OBJS_BNS}
	${CC} ${OBJS_BNS} -o ${NAME_BNS}


clean:
	${RM} ${OBJS} ${OBJS_BNS}

fclean: clean
	${RM} ${NAME} ${NAME_BNS}

re: fclean all