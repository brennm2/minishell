/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:24:21 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/08/08 19:45:12 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	empty_env(t_data *data)
{
	char	pwd[PATH_MAX];
	char	*str;

	if (!have_variable(data->envp, "PWD"))
	{
		getcwd(pwd, sizeof(pwd));
		str = ft_strjoin("PWD=", pwd);
		cpy_env(&data->envp, str);
		free(str);
	}
	if (!have_variable(data->envp, "SHLVL"))
	{
		str = ft_strjoin("SHLVL=", data->shlvl);
		cpy_env(&data->envp, str);
		free(str);
	}
	if (!have_variable(data->envp, "_"))
		cpy_(&data->envp);
}

t_envp	*have_variable(t_envp *env, char *key)
{
	t_envp	*aux_env;

	aux_env = env;
	while (aux_env)
	{
		if (!ft_strncmp(aux_env->key, key, ft_strlen(key)))
			return (aux_env);
		aux_env = aux_env->next;
	}
	return (NULL);
}

void	shlvl_env(t_data *data)
{
	char	*shlvl;

	shlvl = ft_strjoin("SHLVL=", data->shlvl);
	cpy_env(&data->envp, shlvl);
	free(shlvl);
}

void	get_env(t_data *data, char **env)
{
	int		i;

	i = -1;
	data->envp = NULL;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "HOME", 4))
			data->home = ft_strdup(env[i] + 5);
		if (!ft_strncmp(env[i], "_", 1))
		{
			cpy_(&data->envp);
			continue ;
		}
		if (!ft_strncmp(env[i], "SHLVL", 5))
		{
			shlvl_env(data);
			continue ;
		}
		cpy_env(&data->envp, env[i]);
	}
	if (!env[0] || !have_variable(data->envp, "PWD") || \
		!have_variable(data->envp, "SHLVL"))
		empty_env(data);
}
