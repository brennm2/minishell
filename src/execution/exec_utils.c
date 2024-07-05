/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 10:04:02 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/07/05 10:41:03 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	safe_fork(t_data *data)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		printf("Fork failed\n");
		exit(1);
	}
	return (pid);
}

char	**change_env(t_envp *envp)
{
	char	**env;
	t_envp	*envp_aux;
	int		i;

	envp_aux = envp;
	i = 0;
	while(envp_aux)
	{
		i++;
		envp_aux = envp_aux->next;
	}
	env = ft_calloc(i + 1, sizeof(char *));
	envp_aux = envp;
	i = -1;
	while(envp_aux)
	{
		env[++i] = ft_strdup(envp_aux->key);
		env[i] = ft_strjoin_ex(env[i], ":");
		env[i] = ft_strjoin_ex(env[i], envp_aux->value);
		envp_aux = envp_aux->next;
	}
	env[++i] = NULL;
	return (env);
}

void	safe_execve(t_data *data, char **argv, char *path)
{
	char	**env;

	env = change_env(data->envp);
	if(execve(path, argv, env) == -1)
	{
		perror(path);
		if (access(argv[0], X_OK))
			exit(126);
		exit(1);
	}
}

void	safe_pipe(int fd[2], t_data *data)
{
	if (pipe(fd) < 0)
		exit(1);
}
