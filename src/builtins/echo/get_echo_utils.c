/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_echo_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:39:25 by bde-souz          #+#    #+#             */
/*   Updated: 2024/08/07 11:41:10 by bde-souz         ###   ########.fr       */
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
