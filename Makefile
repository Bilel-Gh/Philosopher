# /* ~~~~~~ SOURCES ~~~~~~ */
SRCS_DIR = ./src/
SRCS =	main.c \
		parse.c \
		utils.c \
		time.c \
		actions.c \
		check_death.c \
		init_infos.c \
		init_philo.c \
		start.c \
		stop.c \

OBJS = ${addprefix ${SRCS_DIR}, ${SRCS:.c=.o}}


CHECK_OBJS = ${addprefix ${CHECKER_DIR}, ${CHECKER:.c=.o}}


# /* ~~~~~~~ COMPILING INFO ~~~~~~~ */
CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread -g
IFLAGS:= -I ./include

# /* ~~~~~~~ OTHER ~~~~~~~ */
NAME = philo
RM = rm -f

# /* ~~~~~~~ Colors ~~~~~~~ */
BLACK:="\033[1;30m"
RED:="\033[1;31m"
GREEN:="\033[1;32m"
PURPLE:="\033[1;35m"
CYAN:="\033[1;36m"
WHITE:="\033[1;37m"
EOC:="\033[0;0m"

all:	${NAME}

$(NAME): $(OBJS)
	@echo $(CYAN) " - Compiling $@" $(RED)
	@$(CC) $(CFLAGS) $(OBJS) $(OBJS_UTILS) $(IFLAGS) -o $(NAME)
	@echo $(GREEN) "[OK COMPILED]" $(EOC)
	@echo $(GREEN) "[LAUNCH PROGRAMM]" $(EOC)

clean:
		@echo $(PURPLE) "[🧹Cleaning...🧹]" $(EOC)
		@${RM} ${OBJS} ${CHECK_OBJS}
		@${RM} -r ${OBJ_DIR}

fclean: clean
		@echo $(PURPLE) "[🧹FCleaning...🧹]" $(EOC)
		@${RM} ${OBJS} ${CHECK_OBJS} ${NAME}

re: 	fclean all

.PHONY: all clean fclean re
