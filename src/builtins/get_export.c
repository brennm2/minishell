/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:42:30 by bde-souz          #+#    #+#             */
/*   Updated: 2024/06/26 15:11:05 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_envp	*duplicate_next_node(t_envp *duplicate_env, t_envp *temp_env)
{
	if (temp_env->next)
	{
		duplicate_env->next = ft_calloc(1, sizeof(t_envp));
		duplicate_env = duplicate_env->next;
	}
	else
		duplicate_env->next = NULL;
	return (duplicate_env);
}

t_envp	*duplicate_envp_list(t_envp *env)
{
	t_envp *duplicate_env;
	t_envp *temp_env;
	t_envp *head;

	temp_env = env; //env temporaria
	head = NULL; // env para marcar o comeco
	duplicate_env = ft_calloc(1, sizeof(t_envp));
	if (duplicate_env == NULL)
		return (NULL);
	while (temp_env)
	{
		duplicate_env->key = ft_strdup(temp_env->key);
		duplicate_env->value = ft_strdup(temp_env->value);
		//#TODO lidar com a flag de visivel
		if (!head)
			head = duplicate_env;
		duplicate_env = duplicate_next_node(duplicate_env, temp_env); // Verifica se ha outro node e se e necessario alocar memoria
		temp_env = temp_env->next;
	}
	return (head);
}

t_envp	*organize_envp_list(t_envp *duplicate_env)
{
	t_envp *current_node;
	t_envp *next_node;
	char *key;
	char *value;
	
	current_node = duplicate_env;
	while(current_node->next)
	{
		next_node = current_node->next;
		while(next_node)
		{
			if(ft_strcmp(current_node->key, next_node->key) > 0)
			{
				key = current_node->key;
				value = current_node->value;
				current_node->key = next_node->key;
				current_node->value = next_node->value;
				next_node->key = key;
				next_node->value = value;
			}
			next_node = next_node->next;
		}
		current_node = current_node->next;
	}
	return (duplicate_env);
}

void	create_new_export(t_envp *env, t_token *token)
{
	t_envp	*new_envp;
	char	*temp_str;
	int		i;

	i = 0;
	while (token->str[i] != '=' && token->str[i])
		i++;
	new_envp = env;
	new_envp = find_last_node(new_envp);
	new_envp->next = ft_calloc(1, sizeof(t_token));
	new_envp = new_envp->next;
	new_envp->next = NULL;
	temp_str = ft_strchr(token->str, '=');
	new_envp->value = ft_strdup(temp_str + 1);
	new_envp->key = ft_calloc(sizeof(char *), i + 1);
	ft_strlcpy(new_envp->key, token->str, i + 1);
	//free(new_envp);
	//display_env(env); //DEBUGG <-- RETIRAR
}

void	get_export(t_data *data)
{
	if(!data->token->next)
		print_export(data->envp);
	else if (data->token->next && data->token->next->str[0] == '-')
	{
		ft_putstr_fd("minishell: export: -", 2);
		ft_putchar_fd(data->token->next->str[1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		print_error(NULL, 2);
		return ;
	}
	else if (data->token->next) // Se tiver algo para criar
	{
		// DEBUGG = 42 ERROR! #TODO
		create_new_export(data->envp, data->token->next);
		//printf("Export do comand %s\n", data->token->next->str);
	}
}
