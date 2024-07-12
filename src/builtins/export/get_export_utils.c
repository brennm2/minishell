/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_export_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 14:59:07 by bde-souz          #+#    #+#             */
/*   Updated: 2024/07/12 13:41:30 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	export_error_identifier(t_token *token, t_data *data, int exit_flag)
{
	(void)data;
	(void)exit_flag;
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(token->str, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	//ft_exit_flag(1, exit_flag, data);
	//set_exit_code(1, data);
	//print_error(NULL, 1, data);
}

bool	is_valid_export(t_token *token, t_data *data, int exit_flag)
{
	if (ft_strchr(token->str, '=') == NULL && ft_strchr(token->next->str, '=')) // Se não encontrar '=' no node atual ("VAR = 42")
	{
		while (token->next)
		{
			export_error_identifier(token, data, exit_flag);
			token = token->next;
		}
		return (false);
	}
	return (true);
}

t_envp	*find_last_node(t_envp *lst)
{
	if (lst == 0)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	display_env_export(t_envp *envp, t_data *data, int exit_flag)
{
	while (envp)
	{
		if (envp->invisible == 0)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(envp->key, 1);
			ft_putchar_fd('=', 1);
			ft_putstr_fd("\"", 1);
			ft_putstr_fd(envp->value, 1);
			ft_putstr_fd("\"", 1);
			ft_putchar_fd('\n', 1);
		}
		else if (envp->invisible == 1)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(envp->key, 1);
			ft_putchar_fd('\n', 1);
		}
		envp = envp->next;
	}
	return (ft_exit_flag(0, exit_flag, data));
	//return (set_exit_code(0, data));
}

void	print_export(t_envp *env, t_data *data, int exit_flag)
{
	t_envp	*duplicate_env;

	duplicate_env = duplicate_envp_list(env);
	duplicate_env = organize_envp_list(duplicate_env);
	display_env_export(duplicate_env, data, exit_flag);
	free_env(duplicate_env);
}
