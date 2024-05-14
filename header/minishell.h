#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <linux/limits.h>


typedef struct s_commands
{
	char *commands;
	char *arg;
}				t_commands;


void	getPWD(void);

#endif