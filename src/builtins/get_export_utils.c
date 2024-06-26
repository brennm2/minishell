/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_export_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 14:59:07 by bde-souz          #+#    #+#             */
/*   Updated: 2024/06/26 13:57:34 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

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
	free(duplicate_env); // #TODO Free correto do dup;
}