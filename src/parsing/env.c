/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:24:21 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/06/21 18:36:28 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static t_envp	*ft_lstnew_env(void *key, void *value)
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

static void	ft_lstadd_back_env(t_envp **lst, t_envp *new)
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

static void	cpy_env(t_envp **env, char *str)
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

void	get_env(t_data *data, char **env)
{
	int		i;

	i = -1;
	data->envp = NULL;
	data->home = NULL;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "HOME", 4))
			data->home = ft_strdup(env[i] + 5);
		cpy_env(&data->envp, env[i]);
	}
}
