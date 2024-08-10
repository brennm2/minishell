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
	src/main_utils.c \
	src/exit_code.c \
	src/signal/signal.c \
	src/signal/signal_utils.c \
	src/signal/signal_utils_2.c \
	src/parsing/check_first/check_first.c \
	src/parsing/check_first/check_first_redir.c \
	src/parsing/check_first/check_first_utils.c \
	src/parsing/define_tokens/define_tokens.c \
	src/parsing/define_tokens/define_tokens_utils.c \
	src/parsing/define_tokens/redirects.c \
	src/parsing/here_doc/here_doc.c \
	src/parsing/here_doc/here_doc_expand.c \
	src/parsing/here_doc/here_doc_utils.c \
	src/parsing/here_doc/here_doc_utils_2.c \
	src/parsing/expand/expand.c \
	src/parsing/expand/expand_utils.c \
	src/parsing/expand/expand_utils_2.c \
	src/parsing/expand/expansion.c \
	src/parsing/get_env/env.c \
	src/parsing/get_env/env_utils.c \
	src/parsing/deal_with_buffer/parsing.c \
	src/parsing/deal_with_buffer/moves.c \
	src/parsing/deal_with_buffer/correct_space.c \
	src/parsing/quotes/remove_quotes.c \
	src/parsing/utils.c \
	src/builtins/get_builtins.c \
	src/builtins/echo/get_echo.c \
	src/builtins/echo/get_echo_utils.c \
	src/builtins/pwd/get_pwd.c \
	src/builtins/cd/get_cd.c \
	src/builtins/cd/get_cd_utils.c \
	src/builtins/cd/get_cd_utils_2.c \
	src/builtins/env/get_env.c \
	src/builtins/exit/get_exit.c \
	src/builtins/exit/get_exit_utils.c \
	src/builtins/export/get_export.c \
	src/builtins/export/get_export_utils.c \
	src/builtins/export/get_export_utils_2.c \
	src/builtins/export/get_export_utils_3.c \
	src/builtins/unset/get_unset.c \
	src/error/free.c \
	src/error/free_utils.c \
	src/error/print_error.c \
	src/debug/debug_commands.c \
	src/execution/construction_node.c \
	src/execution/construction_tree.c \
	src/execution/exec_utils.c \
	src/execution/exec_utils_2.c \
	src/execution/execution.c \
	src/execution/path.c \

OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME) sup_file

$(LIBFT):
		$(MAKE) -C ./libs/

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
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
	$(RM) sup

	@echo "\n${YELLOW}--------------------------------"
	@echo "${YELLOW}| ${RED}ALL files ${GREEN}have been cleaned! ${YELLOW}|"
	@echo "${YELLOW}--------------------------------${NC}\n"

norminette:
	@norminette | grep -v "line too long" | grep -v "Comment is invalid in this scope" | grep -v "libs"

valgrind: sup_file
	@make re
	@make sup_file
	@valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=sup --tool=memcheck ./minishell
run:
	@make
	@./minishell

sync_shell: all		## Test w/ syncshell
	@echo "[Testing with syncshell]"
	tmux split-window -h "./$(NAME)"
	tmux setw synchronize-panes on
	clear && bash


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

