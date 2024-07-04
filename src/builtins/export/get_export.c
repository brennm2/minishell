/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:42:30 by bde-souz          #+#    #+#             */
/*   Updated: 2024/07/03 16:37:26 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

t_envp	*duplicate_envp_list(t_envp *env)
{
	t_envp	*duplicate_env;
	t_envp	*temp_env;
	t_envp	*head;

	temp_env = env;
	head = NULL;
	duplicate_env = ft_calloc(1, sizeof(t_envp));
	if (duplicate_env == NULL)
		return (NULL);
	while (temp_env)
	{
		duplicate_env->key = ft_strdup(temp_env->key);
		duplicate_env->value = ft_strdup(temp_env->value);
		duplicate_env->invisible = temp_env->invisible;
		if (!head)
			head = duplicate_env;
		duplicate_env = duplicate_next_node(duplicate_env, temp_env); // Verifica se ha outro node e se e necessario alocar memoria
		temp_env = temp_env->next;
	}
	return (head);
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
	new_envp->key = key;
}

bool	change_existing_export(t_envp *env, char *key, char *value)
{
	if (get_in_env(env, key) == NULL) // Se procurou na lista e não encontrou, então retorna falso
	{
		return (false);
	}
	if (ft_strcmp(key, get_in_env(env, key))) // Se achar Key igual no env
	{
		change_in_env(env, value, key);
		free(key);
		return (true);
	}
	return (false);
}

void	handle_export_token(t_data *data, t_token *token)
{
	char	*value;
	char	*key;

	if (token->str[0] == '=' || token->str[0] == '-') //se tiver '=' ou '-' no comeco
	{
		export_error_identifier(token);
		return ;
	}
	key = find_key(token->str);
	value = ft_strchr(token->str, '=');
	if (value) //Se existir value, anda para frente uma casa, para tirar o "="
		value = value + 1;
	if (!is_invalid_token(key)) //Se for uma key valida
	{
		free(key);
		export_error_identifier(token);
		return ;
	}
	if (!change_existing_export(data->envp, key, value))
		create_new_export(data->envp, key, value);
}

void	get_export(t_data *data)
{
	t_token	*head;

	head = data->token;
	if (!data->token->next)
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
		return (export_error_identifier(data->token->next));
	while (data->token->next) // Se tiver algo para criar
	{
		data->token = data->token->next;
		handle_export_token(data, data->token);
	}
	data->token = head;
}
