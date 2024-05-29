MAKEFLAGS += -s

NAME = minishell

LIBFT = ./libs/libft.a

CC = gcc -g
CCFLAGS = -Wall -Werror -Wextra 
RM = rm
RMFLAGS= -f
GREEN=\033[0;32m
RED=\033[0;31m
YELLOW=\033[1;93m
NC=\033[0m

SRC = src/main.c \
	src/utils.c \
	src/builtins/get_builtins.c \
	src/builtins/get_echo.c \
	src/parsing/parsing.c \
	src/parsing/moves.c \
	src/parsing/check_first.c \
	src/error/free.c \
	src/error/print_error.c \
	src/debug/debug_commands.c \
	src/parsing/env.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(LIBFT):
		$(MAKE) -C ./libs/

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CCFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline


	@echo "\n${YELLOW}--------------------------"
	@echo "${YELLOW}| ${GREEN}All files are compiled ${YELLOW}|"
	@echo "${YELLOW}--------------------------${NC}\n"


clean:
	$(RM) $(RMFLAGS) $(OBJ) $(LIBFT)

	@echo "\n${YELLOW}-----------------------------"
	@echo "${YELLOW}| ${GREEN}Cleaned all ${RED}program${GREEN} files ${YELLOW}|"
	@echo "${YELLOW}-----------------------------${NC}\n"

fclean: clean
	$(RM) $(RMFLAGS) $(NAME) $(OBJ) $(LIBFT)

	@echo "\n${YELLOW}--------------------------------"
	@echo "${YELLOW}| ${RED}ALL files ${GREEN}have been cleaned! ${YELLOW}|"
	@echo "${YELLOW}--------------------------------${NC}\n"

re: fclean all
