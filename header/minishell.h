#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <linux/limits.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

# define S_QUOTES 39
# define D_QUOTES 34

typedef enum s_types
{
	flag,
	command,
	builtin,
	redin,
	redout,
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
	char *str;
	t_types	type;
	struct s_token *next;
}				t_token;


typedef struct s_data
{

	t_envp *envp;
	t_token *token;
	struct s_data	*next;
}				t_data;


void	getPWD(t_data *data);
void	getCD(t_data *data);
void	getECHO(t_data *data);

//MAIN
void	init_commands(char *buffer, t_data *data);


// SRC/UTILS
void	init_token(t_token *token, char *buffer);
void 	init_data(t_data *data, char *buffer);

//SRC/PARSING
int	get_command(char *buffer, t_data *data);
int	get_flags(char *buffer, int i, t_data *data);
int	get_value(char *buffer, int i, t_data *data);
void	get_split(char *buffer, t_data *data);


# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

#endif

