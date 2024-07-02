/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:42:30 by bde-souz          #+#    #+#             */
/*   Updated: 2024/07/02 12:50:26 by bde-souz         ###   ########.fr       */
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
		duplicate_env->invisible = temp_env->invisible;
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
	int		invisible;
	
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
				invisible = current_node->invisible;
				current_node->key = next_node->key;
				current_node->value = next_node->value;
				current_node->invisible = next_node->invisible;
				next_node->key = key;
				next_node->value = value;
				next_node->invisible = invisible;
			}
			next_node = next_node->next;
		}
		current_node = current_node->next;
	}
	return (duplicate_env);
}

void	create_new_export(t_envp *env, char *key, char *value)
{
	t_envp	*new_envp;
	
	new_envp = env;
	new_envp = find_last_node(new_envp);
	new_envp->next = ft_calloc(1, sizeof(t_envp));
	new_envp = new_envp->next;
	
	if (!value)
	{
		new_envp->invisible = 1;
		new_envp->value = ft_strdup("\0");
	}
	else
		new_envp->value = ft_strdup(value);
	new_envp->key = key; //ft_strdup(key);
}

bool	change_existing_export(t_envp *env, char *key, char *value)
{
	if (get_in_env(env, key) == NULL) // Se procurou na lista e não encontrou, então retorna falso
	{
		//free(key);
		return (false);
	}
	if(ft_strcmp(key, get_in_env(env, key))) // Se achar Key igual no env
	{
		change_in_env(env, value, key);
		//free(key);
		return (true);
	}
	//free(key); // Se não achar nada igual, então retorna falso
	return(false);
}

bool	is_invalid_token(char *key)
{
	int	i;

	i = 0;
	if (!ft_isalpha(key[0]) && ft_isdigit(key[0]))
		return (false);
	while(key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_' && key[i] != '=' && key[i] != ' ')
			return false;
		if (key[i] && key[i + 1] == ' ')
			return false;
		i++;
	}
	return true;
}

char	*find_key(char *str)
{
	int		i;
	char	*temp_str;

	i = 0;
	while(str[i] && str[i] != '=')
		i++;
	temp_str = ft_calloc(i + 1, sizeof(char *));
	ft_strlcpy(temp_str, str, i + 1);
	return (temp_str);
}

void	handle_export_token(t_data *data, t_token *token)
{
	char *value;
	char *key;
	
	if (token->str[0] == '=' || token->str[0] == '-') //se tiver '=' ou '-' no comeco
	{
		export_error_identifier(token);
		return;
	}
	key = find_key(token->str);
	value = ft_strchr(token->str, '=');
	if (value) //Se existir value, anda para frente uma casa, para tirar o "="
		value = value + 1;
	if (!is_invalid_token(key)) //Se for uma key valida
	{
		free(key);
		export_error_identifier(token);
		return;
	}
	if(!change_existing_export(data->envp, key, value))
		create_new_export(data->envp, key, value);
}

void	get_export(t_data *data)
{
	t_token	*head;
	
	head = data->token;
	if(!data->token->next)
		return (print_export(data->envp));
	else if (data->token->next && data->token->next->str[0] == '-')
	{
		ft_putstr_fd("minishell: export: -", 2);
		ft_putchar_fd(data->token->next->str[1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		print_error(NULL, 2);
		return ;
	}
	else if (data->token->next->str[0] == '\0')
		return(export_error_identifier(data->token->next));
	while (data->token->next) // Se tiver algo para criar
	{
		data->token = data->token->next;
		handle_export_token(data, data->token);
	}
	data->token = head;
}
