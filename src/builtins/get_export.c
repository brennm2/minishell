/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:42:30 by bde-souz          #+#    #+#             */
/*   Updated: 2024/06/21 15:16:37 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

// void	display_env_export(t_envp *envp)
// {
// 	while (envp)
// 	{
// 		ft_putstr_fd("declare -x ", 1);
// 		ft_putstr_fd(envp->key, 1);
// 		ft_putchar_fd('=', 1);
// 		ft_putstr_fd(envp->value, 1);
// 		ft_putchar_fd('\n', 1);
// 		envp = envp->next;
// 	}
// 	return (set_exit_code(0));
// }

// void	print_export(t_envp *env)
// {
// 	t_envp *duplicate_env;

// 	duplicate_env = duplicate_envp_list(env);
// 	duplicate_env = organize_envp_list(duplicate_env);
// 	display_env_export(duplicate_env);
// 	free(duplicate_env);
// }

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
		duplicate_env = duplicate_next_node(duplicate_env, temp_env);
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

void	get_export(t_data *data)
{
	if(!data->token->next)
	{
		print_export(data->envp); //#TODO Corrigir error de valgrind
	}
	else if (data->token->next && data->token->next->str[0] == '-')
	{
		printf("Error de flag\n");
	}
	else if (data->token->next)
	{
		printf("Export do comand %s\n", data->token->next->str);
	}
}