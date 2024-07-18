/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:46:56 by bde-souz          #+#    #+#             */
/*   Updated: 2024/07/18 14:33:27 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <linux/limits.h>
# include <fcntl.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>

// ----- COLORS -----
# define C_BLUE "\e[1;34m"
# define C_GREEN "\e[1;32m"
# define C_YELLOW "\e[1;93m"
# define C_MAGENTA "\e[1;35m"
# define C_CYAN "\e[1;96m"
# define C_RED "\e[6;31m"
# define END_COLOR "\e[0m"
// ------------------

// DEFINE DOUBLE QUOTES AND SINGLE QUOTES
# define S_QUOTES 39
# define D_QUOTES 34

// DEFINE ERROS
# define ERROR_PIPE_DOUBLE "syntax error near unexpected token `||'"
# define ERROR_PIPE_SINGLE "syntax error near unexpected token `|'"
# define ERROR_PIPE_FINAL "no support for this type of pipe"
# define ERROR_REDIR "syntax error near unexpected token `newline'"
# define ERROR_REDIR_1 "syntax error near unexpected token `<'"
# define ERROR_QUOTE "quotation has not been closed"
# define ERROR_CD_MANY_ARGUMENT "cd: too many arguments"



typedef enum s_builtins
{
	not_builtin,
	echo,
	cd,
	pwd,
	export,
	unset,
	env,
	n_exit,
}			t_builtins;

typedef enum s_types
{
	string,
	flag,
	command,
	builtin,
	redin,
	redout,
	append,
	expander,
	is_pipe,
	here_doc,
	not_expander,
	MAIN,
	CHILD,
	HERE_DOC,
	PIPE,
	IGNORE,
}				t_types;

typedef enum e_tree_type
{
	t_exec,
	t_redir,
	t_pipe
}				t_tree_type;

typedef struct s_token
{
	char		*str;
	char		*exp;
	t_types		type;
	t_builtins	builtin;
	struct s_token		*next;
}				t_token;

//tree structs
typedef struct s_tree_root
{
	t_token		*token;
	t_tree_type	type;
}				t_tree_root;

typedef struct s_tree_pipe
{
	t_token		*token;
	t_tree_type	type;
	t_tree_root	*left;
	t_tree_root	*right;
}				t_tree_pipe;

typedef struct s_tree_red
{
	t_token		*token;
	t_tree_type	type;
	t_tree_root	*tree;
	char		*file;
	char		*exp;
	int			mode;
	int			fd;
	int			perm;
}				t_tree_red;

typedef struct s_tree_exec
{
	t_token		*token;
	t_tree_type	type;
	t_token		*builtin_token;
	char		*cmd;
	char		**argv;
}				t_tree_exec;

//general structs
typedef struct s_envp
{
	char			*key;
	char			*value;
	int				invisible;
	struct s_envp	*next;
}					t_envp;

typedef struct s_data
{
	t_envp *envp;
	t_token *token;
	char	*home;
	char	*ex_;
	int		fd;
	t_tree_root	*tree;
	int		exit_code;
	struct s_data	*next;
}				t_data;

//VARIAVEL GLOBAL
extern int	G_EXIT_CODE;
//


//MAIN
void	init_commands(char *buffer, t_data *data);


// SRC/BUILTIN/GET_BUILTINS
void	get_builtin(t_data *data, t_token *token, int flag);
void	command_not_found(char *str, t_data *data);
void	ft_exit_flag(int exit_code, int exit_flag, t_data *data);

// SRC/BUILTIN/ECHO/GET_ECHO
void	get_echo(t_token *token, t_data *data, int flag);

// SRC/BUILTIN/PWD/GET_PWD
void	get_pwd(t_token *token, t_data *data, int exit_flag);

// SRC/BUILTIN/CD/GET_CD
void	get_cd(t_data *data, t_token *token, int exit_flag);

// SRC/BUILTIN/CD/GET_CD_UTILS
void	cd_error_invalid_option(t_data *data, int exit_flag);
void	cd_error_invalid_file(t_data *data, int exit_flag);
char	*get_in_env(t_envp *envp, char *key);
t_envp	*change_in_env(t_envp *envp, char *cwd, char *key);
void	cd_error_no_file(t_data *data, int exit_flag);

// SRC/BUILTIN/ENV/GET_ENV
void	get_builtin_env(t_data *data, t_token *token, int exit_flag);
void	display_env(t_envp *envp, t_data *data, int exit_flag);

// SRC/BUILTINS/EXIT/GET_EXIT
void	get_exit(t_data *data, t_token *token, int exit_flag);

// SRC/BUILTIN/EXPORT/GET_EXPORT
void	get_export(t_data *data, t_token *token, int exit_flag);
t_envp	*duplicate_envp_list(t_envp *env);
t_envp	*duplicate_next_node(t_envp *duplicate_env, t_envp *temp_env);
t_envp	*organize_envp_list(t_envp *duplicate_env);

// SRC/BUILTIN/EXPORT/GET_EXPORT_UTILS
void	display_env_export(t_envp *envp, t_data *data, int exit_flag);
void	print_export(t_envp *env, t_data *data, int exit_flag);
t_envp	*find_last_node(t_envp *lst);
bool	is_valid_export(t_token *token);
void	export_error_identifier(t_token *token);

// SRC/BUILTIN/EXPORT/GET_EXPORT_UTILS_2
char	*find_key(char *str);
bool	is_invalid_token(char *key);
t_envp	*duplicate_next_node(t_envp *duplicate_env, t_envp *temp_env);
t_envp	*organize_envp_list(t_envp *duplicate_env);

// SRC/BUILTIN/EXPORT/GET_EXPORT_UTILS_3
bool	check_invalid_token(t_token *token);

// SRC/BUILTIN/UNSET/GET_UNSET
void	get_unset(t_data *data, t_token *token, int exit_flag);


// SRC/SIGNAL/SIGNAL
void	ft_catch_signal(int fd);
void	ft_signal_ignore(void);
void	signal_heredoc_checker(int status);

// SRC/UTILS
void	init_token(t_token *token, char *buffer);
void	init_next_token(t_token *token, int len);
void	init_data(t_data *data, char *buffer);
void	set_exit_code(int code, t_data *data);
int		ft_strcmp(char *s1, char *s2);

// SRC/PARSING/CHECK_FIRST
bool	valid_input(char *buffer, t_data *data);


/* ************************************************************************** */
/*                                                                            */
/* -------------------------- SRC/PARSING/PARSING --------------------------- */
/*                                                                            */
/* ************************************************************************** */
//
/**
 * @brief Itera buffer para dentro da <DATA->TOKEN->STR> e, caso exista buffer,
 * cria mais uma lista usando <DATA->TOKEN->NEXT>
 * @param buffer BUFFER da string
 * @param start START da string para ser salva
 * @param end END da string para ser salva
 * @param data Estrutura de <DATA>
 * @return <VOID>
 */
void	save_substring(char *buffer, int start, int end, t_data *data);
/**
 * @brief Função para executar o split dos comandos.
 * @param buffer String de buffer para ser "splitado"
 * @param data A Estrutura de <DATA> para ser utilizada
 * @return <VOID>
 */
void	get_split(char *buffer, t_data *data);

/* ************************************************************************** */
/*                                                                            */
/* -------------------------- SRC/PARSING/MOVES ----------------------------- */
/*                                                                            */
/* ************************************************************************** */
//
/**
 * @brief Função move por espaços até encontrar um caractere
 * @param buffer BUFFER da string
 * @param i Iterador de BUFFER
 * @return Iterador de onde o BUFFER parou
 */
int	move_space(char *buffer, int i);
/**
 * @brief Função move e, em seguida, colocar a string em cada NODE de <DATA>,
 * caso NÃO possua D_QUOTES ou S_QUOTES
 * @param buffer BUFFER da string
 * @param i Iterador de BUFFER
 * @param data Estrutura de <DATA>
 * @return Iterador de onde o BUFFER parou
 */
int	move_without_quotes(char *buffer, int i, t_data *data);
/**
 * @brief Função move e, em seguida, colocar a string em cada NODE de <DATA>,
 * caso possua D_QUOTES ou S_QUOTES
 * @param buffer BUFFER da string
 * @param i Iterador de BUFFER
 * @param flag Flag para determinar se é D_QUOTES ou S_QUOTES
 * @param data Estrutura de <DATA>
 * @return Iterador de onde o BUFFER parou
 */
int	move_with_quotes(char *buffer, int i, int flag, t_data *data);


/* ************************************************************************** */
/*                                                                            */
/* -------------------------- SRC/DEBUG ------------------------------------- */
/*                                                                            */
/* ************************************************************************** */
//
/**
 * @brief Função de Debug para imprimir o que está na lista de Token.
 * @param data Estrutura de <DATA> para iterar até chegar ao NULL de data->str
 * @return <VOID>
 */
void	debug_print_list(t_data *data);
t_data	*debug_get_builtin_type(t_data *data);

//
/* ************************************************************************** */
/*                                                                            */
/* -------------------------- SRC/ERROR/FREE -------------------------------- */
/*                                                                            */
/* ************************************************************************** */
//
void	ft_free_data(t_data *data, int option);
void	free_env(t_envp *envp);
void	free_token(t_token *token);
void	free_data(t_data *data);

// SRC/ERROR/PRINT_ERROR
void	print_error(char *error_type, int error_code, t_data *data);
void	print_error_flag(char *error_type, int error_code, t_data *data,
	int exit_flag);

/* ************************************************************************** */
/*                                                                            */
/* -------------------------- SRC/PARSING/ENV ------------------------------- */
/*                                                                            */
/* ************************************************************************** */
//
/**
 * @brief Extracts the environment variables from the provided array and stores
 * them in a linked list.
 * @param data A pointer to a t_data structure. This structure will hold the 
 * linked list of environment variables.
 * @param env An array of strings, where each string is an environment variable
 * in the format "key=value".
 */
void	get_env(t_data *data, char **env);

/**
 * @brief Expands environment variables in the tokens of a command.
 * @param data A pointer to a t_data structure. This structure contains
 * the tokens of the command to be expanded.
 */
void	expand(t_data *data);

/**
 * @brief Classifies the type of each token in the provided linked list.
 * @param token A pointer to the first token in a linked list. Each token in the list
 * should have its content already set, and this function will set the type of each token.
 */
void	tokenize(t_data *data);

/**
 * @brief Checks and corrects the spacing in a command string.
 * @param buffer A pointer to the command string to be checked and corrected.
 * @return A pointer to the corrected command string.
 */
char	*check_spaces(char *buffer);

void	remove_quotes(t_data *data);
int		deal_quotes(char *token, int i);

/* ************************************************************************** */
/*                                                                            */
/* -------------------------- SRC/PARSING/UTILS ----------------------------- */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Checks if a character is a special character.
 * @param c An integer representing the ASCII value of a character.
 * @return Returns 1 if the character is special, and 0 otherwise.
 */
int ft_is_especial(int c);

/**
 * @brief Concatenates two strings.
 * @param s1 A pointer to the first string.
 * @param s2 A pointer to the second string.
 * @return Returns a pointer to the newly created string that is the result of 
 * the concatenation. Returns NULL if the allocation fails.
 */
char	*ft_strjoin_ex(char *s1, char const *s2);

int	quote_status(char *str, int i);
void	is_here_doc(t_data *data);
char	*creat_here_doc_file(int i, int flag);
void	fill_file(t_data *data, char *delimiter, char *here_doc_file, bool flag);
char	*expand_hd(t_data *data, char *buffer, bool flag);
char	*expansion_exit_code_hd(char *buffer, int j, int i, char *exit_code);
int	deal_with_quotes(t_token *token, int i);
void	is_expand_util(t_token *token, t_data *data, int i, int j);
void	check_env(t_token *token, t_envp *env, int j, int i);
void	after_reds(t_data *data);

// execution

t_tree_root	*pipe_struct(t_data *data, t_token *token);
t_tree_root	*exec_struct(t_data *data, t_token *token);
void	get_exec(t_data *data, t_tree_exec *cmd, char *arg);
t_tree_root	*redir_struct(t_data *data, t_tree_root *tree_cmd);
t_tree_root	*const_pipe(t_data *data, t_tree_root *left, t_tree_root *right);
t_tree_root	*const_redir(t_tree_root *scmd, char *file, int mode, int fd);
t_tree_root	*get_red(t_tree_root *red_cmd);
t_tree_root	*const_exec(t_data *data, t_token *token);
int	count_args(t_data *data, t_token *token);
void pipe_child_execution(t_data *data, t_tree_root *tree, int fd[2], int proc);
void	safe_pipe(int fd[2], t_data *data);
void	safe_execve(t_data *data, t_tree_exec *exec);
char	**change_env(t_envp *envp);
int		safe_fork(t_data *data);
void	execution(t_data *data);
void	executing_tree(t_data *data, t_tree_root *tree);
void	pipe_execution(t_data *data, t_tree_root *tree);
void	redir_execution(t_data *data, t_tree_root *tree);
void	exec_execution(t_data *data, t_tree_root *tree);
void	cmd_execution(t_data *data, t_tree_exec *tree);
char	*get_path(t_data *data, char *cmd);
void	free_token(t_token *token);
void	clean(t_data *data, int ex);
void	*ptr_free(char **ptr);
void	*safe_calloc(size_t bytes, size_t n, t_data *data);
void	free_token_redir(t_token *token);
void	unlink_here_doc_file(void);
bool	is_red_or_pipe(t_token *token);
void	free_tree(t_tree_root *cmd);
void	which_command(t_token *token);


#endif