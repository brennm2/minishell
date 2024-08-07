/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:41:25 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/08/07 14:43:02 by nsouza-o         ###   ########.fr       */
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
