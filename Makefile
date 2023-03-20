# /* ~~~~~~ SOURCES ~~~~~~ */
SRCS_DIR = ./src/
SRCS =	main.c \
		parse.c \
		utils.c \
		time.c \
		actions.c \

OBJS = ${addprefix ${SRCS_DIR}, ${SRCS:.c=.o}}


CHECK_OBJS = ${addprefix ${CHECKER_DIR}, ${CHECKER:.c=.o}}


# # /* ~~~~~~~ INCLUDING LIBFT ~~~~~~~ */
# LIBFT_DIR = libft
# LIBFT_MAKE = Makefile
# LIBFT_PATH = ${LIBFT_DIR}/libft.a

# # /* ~~~~~~~ INCLUDING PRINTF ~~~~~~~ */
# FT_PRINTF_DIR = ft_printf
# FT_PRINTF_MAKE = Makefile
# FT_PRINTF_PATH = ${FT_PRINTF_DIR}/libftprintf.a

# /* ~~~~~~~ COMPILING INFO ~~~~~~~ */
CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread -g
IFLAGS:= -I ./include
# LFLAGS:= -L $(LIBFT_DIR) -lft
# LPRINTF_FLAGS:= -L $(FT_PRINTF_DIR) -lftprintf

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
	# @cd $(LIBFT_DIR) && $(MAKE)
	# @cd $(FT_PRINTF_DIR) && $(MAKE)
	@echo $(CYAN) " - Compiling $@" $(RED)
	@$(CC) $(CFLAGS) $(OBJS) $(OBJS_UTILS) $(IFLAGS) -o $(NAME)
	@echo $(GREEN) "[OK COMPILED]" $(EOC)
	@echo $(GREEN) "[LAUNCH PROGRAMM]" $(EOC)

clean:
		@echo $(PURPLE) "[🧹Cleaning...🧹]" $(EOC)
		@${RM} ${OBJS} ${CHECK_OBJS}
		@${RM} -r ${OBJ_DIR}
		# @make -C ${LIBFT_DIR} -f ${LIBFT_MAKE} clean

fclean: clean
		@echo $(PURPLE) "[🧹FCleaning...🧹]" $(EOC)
		@${RM} ${OBJS} ${CHECK_OBJS} ${NAME}
		# @make -C $(FT_PRINTF_DIR) -f $(FT_PRINTF_MAKE)
		# @cd $(LIBFT_DIR) && $(MAKE) fclean
		# @cd $(FT_PRINTF_DIR) && $(MAKE) fclean

re: 	fclean all

.PHONY: all clean fclean re
