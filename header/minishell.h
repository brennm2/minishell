#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <linux/limits.h>
# include <fcntl.h>


typedef enum s_types
{
	pwd,
	cd,
}				t_types;


typedef struct s_command
{
	char *command;
	int	type;
	t_types *types;
}				t_command;


typedef struct s_data
{
	char *arg;
	t_command *command;
}				t_data;


void	getPWD(void);

// SRC/UTILS
void	init_command(t_command *command);
void	init_data(t_data *data);


# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

#endif