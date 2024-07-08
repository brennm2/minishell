/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:22:27 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/06/28 19:09:02 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*check_command(t_data *data, char *cmd, char *path)
{
	char	*valid_path;
	char	*path_aux;
	
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
		return (cmd);
	valid_path = NULL;
	path_apart = ft_split(path, ':');
	while (path_apart[i])
	{
		valid_path = check_command(data, cmd, path_apart[i]);
		if (valid_path != NULL)
			return (valid_path);
		i++;
	}
	return (valid_path);
}

char	*get_path(t_data *data, char *cmd)
{
	char	*valid_path;
	int		i;
	t_envp	*env_aux;

	i = 0;
	valid_path = NULL;
	env_aux = data->envp;
	while (env_aux)
	{
		if (!ft_strcmp(env_aux->key, "PATH"))
			valid_path = find_path(data, env_aux->value, cmd);
		env_aux = env_aux->next;
	}
	//printf("- %s\n", valid_path);
	return (valid_path);
}
