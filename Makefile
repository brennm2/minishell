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
	src/builtins/get_pwd.c \
	src/builtins/get_cd.c \
	src/builtins/get_env.c \
	src/builtins/get_exit.c \
	src/builtins/get_export.c \
	src/builtins/get_export_utils.c \
	src/parsing/parsing.c \
	src/parsing/moves.c \
	src/parsing/check_first.c \
	src/error/free.c \
	src/error/print_error.c \
	src/debug/debug_commands.c \
	src/parsing/env.c \
	src/parsing/expand.c \
	src/parsing/define_tokens.c \
	src/parsing/correct_space.c \
	src/parsing/utils.c \
	src/parsing/remove_quotes.c

OBJ = $(SRC:.c=.o)

all: $(NAME) sup_file

$(LIBFT):
		$(MAKE) -C ./libs/

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CCFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline


	@echo "\n${YELLOW}--------------------------"
	@echo "${YELLOW}| ${GREEN}All files are compiled ${YELLOW}|"
	@echo "${YELLOW}--------------------------${NC}\n"


clean: sup_file
	$(RM) $(RMFLAGS) $(OBJ) $(LIBFT)
	$(MAKE) -C ./libs/ clean

	@echo "\n${YELLOW}-----------------------------"
	@echo "${YELLOW}| ${GREEN}Cleaned all ${RED}program${GREEN} files ${YELLOW}|"
	@echo "${YELLOW}-----------------------------${NC}\n"

fclean: clean 
	$(RM) $(RMFLAGS) $(NAME) $(OBJ) $(LIBFT)
	$(MAKE) -C ./libs/ fclean

	@echo "\n${YELLOW}--------------------------------"
	@echo "${YELLOW}| ${RED}ALL files ${GREEN}have been cleaned! ${YELLOW}|"
	@echo "${YELLOW}--------------------------------${NC}\n"

norminette:
	@norminette | grep -v "line too long" | grep -v "Comment is invalid in this scope" | grep -v "libs"

valgrind:
	@valgrind --leak-check=full --show-leak-kinds=all --suppressions=sup ./minishell


define SUP_BODY
{
   name
   Memcheck:Leak
   fun:*alloc
   ...
   obj:*/libreadline.so.*
   ...
}
{
    leak readline
    Memcheck:Leak
    ...
    fun:readline
}
{
    leak add_history
    Memcheck:Leak
    ...
    fun:add_history
}
endef

sup_file:
    $(file > sup,$(SUP_BODY))

re: fclean all

.PHONY: sup_file

