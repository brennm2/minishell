/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:42:30 by bde-souz          #+#    #+#             */
/*   Updated: 2024/07/23 15:27:18 by nsouza-o         ###   ########.fr       */
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

void	create_new_export(t_data *data, char *key, char *value, int exit_flag)
{
	t_envp	*new_envp;

	(void) exit_flag;
	new_envp = data->envp;
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
	//ft_exit_flag(0, exit_flag, data);
}

bool	change_existing_export(t_data *data, char *key, char *value,
	int exit_flag)

{
	(void) exit_flag;
	if (get_in_env(data->envp, key) == NULL) // Se procurou na lista e não encontrou, então retorna falso
	{
		return (false);
	}
	if (ft_strcmp(key, get_in_env(data->envp, key))) // Se achar Key igual no env
	{
		change_in_env(data->envp, value, key);
		free(key);
		//ft_exit_flag(0, exit_flag, data);
		return (true);
	}
	return (false);
}

void	handle_export_token(t_data *data, t_token *token, int exit_flag)
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
	if (!is_invalid_token(key)) //Se nao for uma key valida
	{
		free(key);
		export_error_identifier(token);
		return ;
	}
	if (!change_existing_export(data, key, value, exit_flag))
		create_new_export(data, key, value, exit_flag);
}

void	get_export(t_data *data, t_token *token, int exit_flag)
{
	static bool	flag;

	if (!data->envp)
		return ;
	if (!token->next || token->next->type != string)
		return (print_export(data->envp, data, exit_flag));
	if (token->next && token->next->str[0] == '-')
	{
		ft_putstr_fd("minishell: export: -", 2);
		ft_putchar_fd(token->next->str[1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		return (ft_exit_flag(2, exit_flag, data));
	}
	if (token->next->str[0] == '\0')
		return (export_error_identifier(token->next));
	flag = check_invalid_token(token);
	while (token->next && token->next->type == string)
	{
		token = token->next;
		handle_export_token(data, token, exit_flag);
	}
	if (flag == true)
		ft_exit_flag(1, exit_flag, data);
	else
		ft_exit_flag(0, exit_flag, data);
}
