/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_echo_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:39:25 by bde-souz          #+#    #+#             */
/*   Updated: 2024/08/09 11:43:05 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	echo_handle_tidle(t_data *data, t_token *token)
{
	if (token->str[1] == '+')
	{
		if (get_in_env(data->envp, "PWD") == NULL)
			write(1, "~+", 2);
		else
			ft_putstr_fd(get_in_env(data->envp, "PWD"), 1);
	}
	else
	{
		if (get_in_env(data->envp, "OLDPWD") == NULL)
			write(1, "~-", 2);
		else
			ft_putstr_fd(get_in_env(data->envp, "OLDPWD"), 1);
	}
}

bool	need_space(t_token *token)
{
	while (token && (token->type != is_pipe))
	{
		if (token->type == string)
			return (true);
		token = token->next;
	}
	return (false);
}
