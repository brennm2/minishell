/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:24:21 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/07/26 18:35:58 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

t_envp	*ft_lstnew_env(void *key, void *value)
{
	t_envp	*list;
	char	*key_d;
	char	*value_d;

	key_d = (char *)key;
	value_d = (char *)value;
	list = ft_calloc(1, sizeof(t_envp));
	if (!list)
		return (NULL);
	list->key = key_d;
	list->value = value_d;
	list->next = NULL;
	return (list);
}

void	ft_lstadd_back_env(t_envp **lst, t_envp *new)
{
	t_envp	*aux;

	if (!new)
		return ;
	if (!lst || !*lst)
	{
		*lst = new;
		return ;
	}
	aux = *lst;
	while (aux->next != NULL)
		aux = aux->next;
	aux->next = new;
}

void	cpy_env(t_envp **env, char *str)
{
	int		i;
	char	*key;
	char	*value;
	int		size;
	t_envp	*node;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	key = ft_calloc(sizeof(char), (i + 1));
	size = ft_strlen(str) - i;
	value = ft_calloc(sizeof(char), size);
	ft_strlcpy(key, str, i + 1);
	ft_strlcpy(value, str + i + 1, size);
	node = ft_lstnew_env(key, value);
	if (!node)
	{
		free (key);
		free (value);
		return ;
	}
	ft_lstadd_back_env(env, node);
}

void	cpy_(t_envp **env)
{
	char	*key;
	char	*value;
	t_envp	*node;

	key = ft_strdup("_");
	value = ft_strdup("/usr/bin/env");
	node = ft_lstnew_env(key, value);
	if (!node)
	{
		free (key);
		free (value);
		return ;
	}
	ft_lstadd_back_env(env, node);
}

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

void	get_env(t_data *data, char **env)
{
	int		i;
	char	*shlvl;

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
			shlvl = ft_strjoin("SHLVL=", data->shlvl);
			cpy_env(&data->envp, shlvl);
			free(shlvl);
			continue ;
		}
		cpy_env(&data->envp, env[i]);
	}
	if (!env[0] || !have_variable(data->envp, "PWD") || !have_variable(data->envp, "SHLVL"))
		empty_env(data);
}
