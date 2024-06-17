/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:46:56 by bde-souz          #+#    #+#             */
/*   Updated: 2024/06/17 12:20:58 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <linux/limits.h>
# include <fcntl.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

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
	space,
	not_expander,
}				t_types;


typedef struct s_envp
{
	char *key;
	char *value;
	//flag visivel;
	struct s_envp *next;
}					t_envp;


typedef struct s_token
{
	char		*str;
	t_types		type;
	t_builtins	builtin;
	struct s_token		*next;
}				t_token;

typedef struct s_data
{

	t_envp *envp;
	t_token *token;
	struct s_data	*next;
}				t_data;

//VARIAVEL GLOBAL
extern int	G_EXIT_CODE;
//


//MAIN
void	init_commands(char *buffer, t_data *data);


// SRC/BUILTIN/GET_BUILTINS
void	get_builtin(t_data *data);

// SRC/BUILTIN/GET_ECHO
void	get_echo(t_token *token);

// SRC/BUILTIN/GET_PWD
void	get_pwd(t_token *token);

// SRC/BUILTIN/GET_CD
void	get_cd(t_data *data);
char	*get_in_env(t_envp *envp, char *key);

// SRC/BUILTIN/GET_BUILTIN_ENV
void	get_builtin_env(t_data *data);

// SRC/BUILTINS/GET_EXIT
void	get_exit(t_data *data);

// SRC/UTILS
void	init_token(t_token *token, char *buffer);
void	init_data(t_data *data, char *buffer);
void	set_exit_code(int code);
int		ft_strcmp(char *s1, char *s2);

// SRC/PARSING/CHECK_FIRST
bool	valid_input(char *buffer);


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
 *
 * This function iterates over the provided array of environment variables, 
 * copying each one into a new node in a linked list.
 * The linked list is stored in the provided t_data structure.
 *
 * @param data A pointer to a t_data structure. This structure will hold the 
 * linked list of environment variables.
 * @param env An array of strings, where each string is an environment variable
 * in the format "key=value".
 */
void	get_env(t_data *data, char **env);

/**
 * @brief Expands environment variables in the tokens of a command.
 *
 * This function iterates over the tokens in a command and expands any
 * environment variables found within the tokens. The expansion is done
 * in-place, modifying the tokens directly.
 * 
 * @param data A pointer to a t_data structure. This structure contains
 * the tokens of the command to be expanded.
 */
void	expand(t_data *data);

/**
 * @brief Classifies the type of each token in the provided linked list.
 *
 * This function iterates over a linked list of tokens, determining the type of 
 * each token based on its content. The type of each token is stored within 
 * the token itself.
 *
 * @param token A pointer to the first token in a linked list. Each token in the list
 * should have its content already set, and this function will set the type of each token.
 */
void	tokenize(t_data *data);

#endif