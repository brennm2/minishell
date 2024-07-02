/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:26:33 by bde-souz          #+#    #+#             */
/*   Updated: 2024/07/02 11:47:32 by bde-souz         ###   ########.fr       */
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
			printf("achou o node: %s\n", temp_env->next->key); //debug
			//printf("back node: %s\n", temp_env->key);
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
	//free(node->next);
	// node->next = NULL;
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
	printf("back node: %s\n", back_node->key); //Debug

	free_node(dead_node);
}

void	get_unset(t_data *data)
{
	if (!data->token)
		return ;
	if(get_in_env(data->envp, data->token->next->str) == NULL)
	{
		printf("Nao achou nada, unset: %s\n", data->token->next->str);
		return ;
	}
	else
	{
		search_for_node(data->envp, data->token->next);
	}
}