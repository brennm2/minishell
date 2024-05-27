/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:24:21 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/05/27 15:15:59 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static t_envp	*ft_lstnew_env(void *key, void *value)
{
	t_envp	*list;

	list = ft_calloc(sizeof(t_list), 1);
	if (!list)
		return (0); // 
	list->key = key;
	list->value = value;
	list->next = NULL;
	return (list);
}

static void	ft_lstadd_back_env(t_envp **lst, t_envp *new)
{
	t_envp	*aux;

	if (!new)
		return ;
	if (!*lst)
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
	int		j;
	char	*key;
	char	*value;
	int 	size;
	t_envp	*node;
	
	i = -1;
	j = -1;
	while (str[++i] && str[i] != '=')
		;
	key = ft_calloc(sizeof(char), (i + 1));
	size = ft_strlen(str) - i;
	value = ft_calloc(sizeof(char), size);
	i = -1;
	while(str[++i] && (str[i] != '='))
		key[i] = str[i];
	while(str[++i])
		value[++j] = str[i];
	node = ft_lstnew_env(key, value);
	ft_lstadd_back_env(env, node);
}

void	get_env(t_data *data, char **env)
{
	int		i;

	i = -1;
	while (env[++i])
		cpy_env(&data->envp, env[i]);
}
