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
	Pipe //ok
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


void	getPWD(t_data *data);
void	getCD(t_data *data);
void	getECHO(t_data *data);


// SRC/UTILS
void	init_command(t_token *token, char *buffer);
void 	init_data(t_data *data, char *buffer);

//SRC/PARSING
int	get_command(char *buffer, t_data *data);
int	get_flags(char *buffer, int i, t_data *data);
int	get_value(char *buffer, int i, t_data *data);


# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

#endif

