/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:46:56 by bde-souz          #+#    #+#             */
/*   Updated: 2024/07/10 13:15:13 by bde-souz         ###   ########.fr       */
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
	flag, // echo -a, imprime -a;
	command,
	builtin, //ok
	redin, //ok
	redout, //ok
	append, //ok
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

typedef struct s_token
{
	char		*str;
	t_types		type;
	t_builtins	builtin;
	struct s_token		*next;
}				t_token;

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
	struct s_data	*next;
}				t_data;

//VARIAVEL GLOBAL
extern int	G_EXIT_CODE;
//


//MAIN
void	init_commands(char *buffer, t_data *data);


// SRC/BUILTIN/GET_BUILTINS
void	get_builtin(t_data *data);
void	command_not_found(t_token *token);

// SRC/BUILTIN/ECHO/GET_ECHO
void	get_echo(t_token *token, t_data *data);

// SRC/BUILTIN/PWD/GET_PWD
void	get_pwd(t_token *token);

// SRC/BUILTIN/CD/GET_CD
void	get_cd(t_data *data);

// SRC/BUILTIN/CD/GET_CD_UTILS
void	cd_error_invalid_option(t_data *data);
void	cd_error_invalid_file(t_data *data);
char	*get_in_env(t_envp *envp, char *key);
t_envp	*change_in_env(t_envp *envp, char *cwd, char *key);

// SRC/BUILTIN/ENV/GET_ENV
void	get_builtin_env(t_data *data);
void	display_env(t_envp *envp);

// SRC/BUILTINS/EXIT/GET_EXIT
void	get_exit(t_data *data);

// SRC/BUILTIN/EXPORT/GET_EXPORT
void	get_export(t_data *data);
t_envp	*duplicate_envp_list(t_envp *env);
t_envp	*duplicate_next_node(t_envp *duplicate_env, t_envp *temp_env);
t_envp	*organize_envp_list(t_envp *duplicate_env);

// SRC/BUILTIN/EXPORT/GET_EXPORT_UTILS
void	display_env_export(t_envp *envp);
void	print_export(t_envp *env);
t_envp	*find_last_node(t_envp *lst);
bool	is_valid_export(t_token *token);
void	export_error_identifier(t_token *token);

// SRC/BUILTIN/EXPORT/GET_EXPORT_UTILS_2
char	*find_key(char *str);
bool	is_invalid_token(char *key);
t_envp	*duplicate_next_node(t_envp *duplicate_env, t_envp *temp_env);
t_envp	*organize_envp_list(t_envp *duplicate_env);

// SRC/BUILTIN/UNSET/GET_UNSET
void	get_unset(t_data *data);


// SRC/SIGNAL/SIGNAL
void	ft_catch_signal(int fd);
void	ft_signal_ignore(void);
void	signal_child_checker(int status);

// SRC/UTILS
void	init_token(t_token *token, char *buffer);
void	init_next_token(t_token *token, int len);
void	init_data(t_data *data, char *buffer);
void	set_exit_code(int code);
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
void	print_error(char *error_type, int error_code);

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
bool	is_here_doc(t_data *data);
int	deal_with_quotes(t_token *token, int i);
void	is_expand_util(t_token *token, t_envp *envp, int i, int j);
void	check_env(t_token *token, t_envp *env, int j, int i);
void	after_reds(t_data *data);

//execution
bool	nbr_pipes(t_data *data);
void	execution_pipes(t_data *data);
void	cmd_execution(t_data *data);
char	*get_path(t_data *data, char *cmd);
int	safe_fork(t_data *data);
void	safe_execve(t_data *data, char **argv, char *path);
void	safe_pipe(int fd[2], t_data *data);
void	*ptr_free(char **ptr);

#endif