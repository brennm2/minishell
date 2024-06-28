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
VG = valgrind

SRC = src/main.c \
	src/utils.c \
	src/builtins/get_builtins.c \
	src/builtins/get_echo.c \
	src/builtins/get_pwd.c \
	src/builtins/get_cd.c \
	src/builtins/get_env.c \
	src/builtins/get_exit.c \
	src/builtins/get_export.c \
	src/parsing/parsing.c \
	src/parsing/moves.c \
	src/parsing/check_first.c \
	src/error/free.c \
	src/error/print_error.c \
	src/debug/debug_commands.c \
	src/parsing/env.c \
	src/parsing/expand.c \
	src/parsing/expand_utils.c \
	src/parsing/define_tokens.c \
	src/parsing/correct_space.c \
	src/parsing/utils.c \
	src/parsing/remove_quotes.c \
	src/parsing/here_doc.c \
	src/parsing/redirects.c \
	src/execution/construction_tree.c \
	src/execution/construction_node.c \
	src/execution/exec_utils.c \
	src/execution/execution.c \
	src/execution/path.c

OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(LIBFT):
		$(MAKE) -C ./libs/

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) -c $< -o $@
#verificar o $(CC) $(CCFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CCFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline


	@echo "\n${YELLOW}--------------------------"
	@echo "${YELLOW}| ${GREEN}All files are compiled ${YELLOW}|"
	@echo "${YELLOW}--------------------------${NC}\n"


clean:
	$(RM) $(RMFLAGS) $(OBJ) $(LIBFT)
	$(MAKE) -C ./libs/ clean
	$(RM) $(RMFLAGS) -r $(OBJ_DIR)

	@echo "\n${YELLOW}-----------------------------"
	@echo "${YELLOW}| ${GREEN}Cleaned all ${RED}program${GREEN} files ${YELLOW}|"
	@echo "${YELLOW}-----------------------------${NC}\n"

fclean: clean
	$(RM) $(RMFLAGS) $(NAME) $(OBJ) $(LIBFT) $(OBJ_DIR)
	$(MAKE) -C ./libs/ fclean

	@echo "\n${YELLOW}--------------------------------"
	@echo "${YELLOW}| ${RED}ALL files ${GREEN}have been cleaned! ${YELLOW}|"
	@echo "${YELLOW}--------------------------------${NC}\n"

norminette:
	@norminette | grep -v "line too long" | grep -v "Comment is invalid in this scope" | grep -v "libs"

valgrind:
	@valgrind --leak-check=full --show-leak-kinds=all --suppressions=supp.supp ./minishell

re: fclean all

