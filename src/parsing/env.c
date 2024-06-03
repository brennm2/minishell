/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:24:21 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/06/03 10:53:07 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static t_envp	*ft_lstnew_env(void *key, void *value)
{
	t_envp	*list;
	char *key_d;
	char *value_d;

	key_d =(char *)key;
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
	int		j;
	char	*key;
	char	*value;
	int 	size;
	t_envp	*node;
	
	i = 0;
	j = -1;
	// printf("EVN TO COPY: %s\n", str);
	while (str[i] && str[i] != '=')
		i++;
	key = ft_calloc(sizeof(char), (i + 1));
	size = ft_strlen(str) - i;
	value = ft_calloc(sizeof(char), size);
	i = -1;
	while(str[++i] && (str[i] != '='))
		key[i] = str[i];
	key[i] = '\0';
	// printf("KEY COPIED: %s\n", key);
	while(str[++i])
		value[++j] = str[i];
	value[++j] = '\0';
	// printf("VALUE COPIED: %s\n", value);
	node = ft_lstnew_env(key, value);
	if (!node) 
	{
        free(key);
        free(value);
		return ;
	}
	ft_lstadd_back_env(env, node);
}

void	get_env(t_data *data, char **env)
{
	int		i;
	//t_envp *envp;

	i = -1;
	// envp = ft_calloc(1, sizeof(t_envp));
	data->envp = NULL;
	while (env[++i])
	{
		cpy_env(&data->envp, env[i]);
	}
	/* i = 0;
	while (data->envp)
	{
		printf("%d %s = %s\n", i, data->envp->key, data->envp->value);
		printf("-\n"),
		data->envp = data->envp->next;
		i++;
	} */
}
