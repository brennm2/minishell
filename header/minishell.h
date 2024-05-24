/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:46:56 by bde-souz          #+#    #+#             */
/*   Updated: 2024/05/24 14:38:36 by bde-souz         ###   ########.fr       */
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

# define S_QUOTES 39
# define D_QUOTES 34
typedef enum s_builtins
{
	echo,
	cd,
	pwd,
	export,
	unset,
	env,
	Exit
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
	string,
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
	t_builtins	builtin; //Se for um buitin, ja fica definido qual.
	struct t_token		*next;
}				t_token;


typedef struct s_data
{

	t_envp *envp;
	t_token *token;
	struct s_data	*next;
}				t_data;

//test

void	getPWD(t_data *data);
void	getCD(t_data *data);
void	getECHO(t_data *data);

//MAIN
void	init_commands(char *buffer, t_data *data);


// SRC/UTILS
void	init_token(t_token *token, char *buffer);
void 	init_data(t_data *data, char *buffer);

//SRC/PARSING/PARSING
void	save_substring(char *buffer, int start, int end, t_data *data);
void	get_split(char *buffer, t_data *data);

/* ************************************************************************** */
/*                                                                            */
/* -------------------------- SRC/PARSING/MOVES ----------------------------- */
/*                                                                            */
/* ************************************************************************** */
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


// ------------ SRC/DEBUG ------------ //
/**
 * @brief Função de Debug para imprimir o que está na lista de Token.
 * @param data Estrutura de <DATA> para iterar até chegar ao NULL de data->str
 * @return <VOID>
 */
void	debug_print_list(t_data *data);


/* ************************************************************************** */
/*                                                                            */
/* -------------------------- SRC/ERROR/FREE -------------------------------- */
/*                                                                            */
/* ************************************************************************** */

void	free_all(t_data *data);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

#endif

