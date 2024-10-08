/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:22:27 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/08/12 13:43:20 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*check_command(t_data *data, char *cmd, char *path)
{
	char	*valid_path;
	char	*path_aux;

	(void)data;
	valid_path = NULL;
	path_aux = ft_strjoin(path, "/");
	valid_path = ft_strjoin(path_aux, cmd);
	free(path_aux);
	if (access(valid_path, F_OK) == 0)
		return (valid_path);
	free(valid_path);
	return (NULL);
}

char	*find_path(t_data *data, char *path, char *cmd)
{
	char	**path_apart;
	char	*valid_path;
	int		i;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	valid_path = NULL;
	path_apart = ft_split(path, ':');
	while (path_apart[i])
	{
		valid_path = check_command(data, cmd, path_apart[i]);
		if (valid_path != NULL)
		{
			ptr_free(path_apart);
			return (valid_path);
		}
		i++;
	}
	ptr_free(path_apart);
	return (valid_path);
}

char	*get_path(t_data *data, char *cmd)
{
	char	*valid_path;
	t_envp	*env_aux;

	valid_path = NULL;
	env_aux = data->envp;
	while (env_aux)
	{
		if (!ft_strcmp(env_aux->key, "PATH"))
			valid_path = find_path(data, env_aux->value, cmd);
		env_aux = env_aux->next;
	}
	if (!valid_path)
	{
		if (cmd[0] == '/' && !access(cmd, X_OK))
			return (ft_strdup(cmd));
		else if (cmd[0] == '.' && cmd[1] == '/' && !access(cmd, X_OK))
			return (ft_strdup(cmd));
		return (NULL);
	}
	return (valid_path);
}

void	empty_cmd(t_data *data, t_tree_exec *exec)
{
	struct stat	file_stat;

	stat(exec->argv[0], &file_stat);
	if (!ft_strncmp(exec->argv[0], "./", 2) || \
		!ft_strncmp(exec->argv[0], "/", 1))
	{
		if (access(exec->argv[0], F_OK) < 0)
			printf("minishell: %s: No such file or directory\n", exec->argv[0]);
		else if (access(exec->argv[0], X_OK) < 0)
		{
			if (S_ISDIR(file_stat.st_mode))
				printf("minishell: %s: Is a directory\n", exec->argv[0]);
			else
			{
				write(2, "minishell: ", 11);
				perror(exec->argv[0]);
			}
			clean(data, 126);
		}
	}
	else
		command_not_found(exec->argv[0], data);
	clean(data, 127);
}

void	execve_error(t_data *data, char *exec_argv)
{
	if (!ft_strncmp(exec_argv, "./", 2) || \
		!ft_strncmp(exec_argv, "/", 1))
	{
		printf("minishell: %s: Is a directory\n", exec_argv);
		data->exit_code = 126;
	}
	else
	{
		ft_putstr_fd(exec_argv, 2);
		ft_putstr_fd(": command not found\n", 2);
		data->exit_code = 127;
	}
}
