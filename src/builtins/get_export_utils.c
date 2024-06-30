/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_export_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 14:59:07 by bde-souz          #+#    #+#             */
/*   Updated: 2024/06/28 13:10:00 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

bool	is_valid_export(t_token *token)
{
	//char	*temp_str;
	
	if(ft_strchr(token->str, '=') == NULL && ft_strchr(token->next->str, '=')) // Se não encontrar '=' no node atual ("VAR = 42")
	{
		while(token->next)
		{
			ft_putstr_fd("minishell: export: '", 2);
			ft_putstr_fd(token->next->str, 2);
			ft_putendl_fd("': not a valid identifier", 2);
			token = token->next;
		}
		print_error(NULL, 1);
		return (false);
	}
	// if ()
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
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(envp->key, 1);
		ft_putchar_fd('=', 1);
		ft_putstr_fd("\"", 1);
		ft_putstr_fd(envp->value, 1);
		ft_putstr_fd("\"", 1);
		ft_putchar_fd('\n', 1);
		envp = envp->next;
	}
	return (set_exit_code(0));
}

void	print_export(t_envp *env)
{
	t_envp *duplicate_env;

	duplicate_env = duplicate_envp_list(env);
	duplicate_env = organize_envp_list(duplicate_env);
	display_env_export(duplicate_env);
	free_env(duplicate_env);
	//free(duplicate_env); // #TODO Free correto do dup;
}