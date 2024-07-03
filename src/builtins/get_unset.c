/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:26:33 by bde-souz          #+#    #+#             */
/*   Updated: 2024/07/03 14:13:14 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_envp	*find_back_node_in_env(t_envp *env, char *key)
{
	t_envp	*temp_env;

	temp_env = env;
	while (temp_env->next)
	{
		if (!ft_strcmp(temp_env->next->key, key))
		{
			return (temp_env);
		}
		temp_env = temp_env->next;
	}
	return (NULL);
}

void	free_node(t_envp *node)
{
	free(node->key);
	node->key = NULL;
	free(node->value);
	node->value = NULL;
	free(node);
}

void	search_for_node(t_envp *env, t_token *token)
{
	t_envp	*back_node;
	t_envp	*next_node;
	t_envp	*dead_node;

	back_node = find_back_node_in_env(env, token->str);
	dead_node = back_node->next;
	next_node = back_node->next->next;
	back_node->next = next_node;
	free_node(dead_node);
}

void	get_unset(t_data *data)
{
	t_token	*head;
	int		flag;

	flag = 0;
	head = data->token;
	if (!data->token->next)
		return ;
	while (data->token->next)
	{
		data->token = data->token->next;
		if (flag++ == 0 && data->token->str[0] == '-')
		{
			ft_putstr_fd("minishell: unset: -", 2);
			ft_putchar_fd(data->token->str[1], 2);
			ft_putendl_fd(": invalid option", 2);
			data->token = head;
			return (print_error(NULL, 2));
		}
		if (get_in_env(data->envp, data->token->str) == NULL)
			continue ;
		else
			search_for_node(data->envp, data->token);
	}
	data->token = head;
}
