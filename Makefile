MAKEFLAGS += -s

NAME = minishell

LIBFT = ./libs/libft.a

CC = cc -g
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
	src/builtins/echo/get_echo.c \
	src/builtins/pwd/get_pwd.c \
	src/builtins/cd/get_cd.c \
	src/builtins/cd/get_cd_utils.c \
	src/builtins/env/get_env.c \
	src/builtins/exit/get_exit.c \
	src/builtins/export/get_export.c \
	src/builtins/export/get_export_utils.c \
	src/builtins/export/get_export_utils_2.c \
	src/builtins/unset/get_unset.c \
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
	src/parsing/redirects.c

OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME) sup_file

$(LIBFT):
		$(MAKE) -C ./libs/

$(OBJ_DIR):
		mkdir -p $(OBJ_DIR)
		mkdir -p $(OBJ_DIR)/src
		mkdir -p $(OBJ_DIR)/src/builtins
		mkdir -p $(OBJ_DIR)/src/builtins/export
		mkdir -p $(OBJ_DIR)/src/builtins/cd
		mkdir -p $(OBJ_DIR)/src/builtins/echo
		mkdir -p $(OBJ_DIR)/src/builtins/env
		mkdir -p $(OBJ_DIR)/src/builtins/exit
		mkdir -p $(OBJ_DIR)/src/builtins/pwd
		mkdir -p $(OBJ_DIR)/src/builtins/unset
		mkdir -p $(OBJ_DIR)/src/parsing
		mkdir -p $(OBJ_DIR)/src/error
		mkdir -p $(OBJ_DIR)/src/debug

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CCFLAGS) -c $< -o $@


$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CCFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline


	@echo "\n${YELLOW}--------------------------"
	@echo "${YELLOW}| ${GREEN}All files are compiled ${YELLOW}|"
	@echo "${YELLOW}--------------------------${NC}\n"


clean: sup_file
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
	@valgrind --leak-check=full --show-leak-kinds=all --suppressions=sup --tool=memcheck ./minishell


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

