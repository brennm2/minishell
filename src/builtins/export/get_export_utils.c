/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_export_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 14:59:07 by bde-souz          #+#    #+#             */
/*   Updated: 2024/07/04 10:14:34 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	export_error_identifier(t_token *token)
{
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(token->str, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	print_error(NULL, 1);
}

bool	is_valid_export(t_token *token)
{
	if (ft_strchr(token->str, '=') == NULL && ft_strchr(token->next->str, '=')) // Se não encontrar '=' no node atual ("VAR = 42")
	{
		while (token->next)
		{
			export_error_identifier(token);
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

void	display_env_export(t_envp *envp)
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
	return (set_exit_code(0));
}

void	print_export(t_envp *env)
{
	t_envp	*duplicate_env;

	duplicate_env = duplicate_envp_list(env);
	duplicate_env = organize_envp_list(duplicate_env);
	display_env_export(duplicate_env);
	free_env(duplicate_env);
}
