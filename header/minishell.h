#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <linux/limits.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>


typedef enum s_types
{
	pwd,
	cd,
	echo,
}				t_types;


typedef struct s_envp
{
	char *key;
	char *value;
	//flag visivel;
	struct s_envp *next;
}					t_envp;


typedef struct s_command
{
	char *command;
	char *value;
	t_types	type;
	//flag visivel
	struct s_command *next;
}				t_command;


typedef struct s_data
{

	t_envp envp;
	t_command *command;
	struct s_data	*next;
}				t_data;


void	getPWD(t_data *data);
void	getCD(t_data *data);
void	getECHO(t_data *data);


// SRC/UTILS
void	init_command(t_command *command, char *buffer);
void 	init_data(t_data *data, char *buffer);


# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

#endif