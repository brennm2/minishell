/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:45:52 by bde-souz          #+#    #+#             */
/*   Updated: 2024/08/08 13:35:18 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	pwd_option_error(t_data *data, t_token *token, int exit_flag)
{
	write(2, "minishell: pwd: -", 17);
	write(2, &token->next->str[1], 1);
	write(2, ": invalid option\n", 17);
	ft_exit_flag(2, exit_flag, data);
}

void	get_pwd(t_token *token, t_data *data, int exit_flag)
{
	char	cwd[256];

	if (token->next)
	{
		if (token->next->str[0] == '-' && token->next->str[1])
			return (pwd_option_error(data, token, exit_flag));
	}
	if (get_in_env(data->envp, "PWD") == NULL)
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			ft_putendl_fd("", 1);
		else
			ft_putendl_fd(cwd, 1);
	}
	else
	{
		ft_putstr_fd(get_in_env(data->envp, "PWD"), 1);
		ft_putchar_fd('\n', 1);
	}
	return (ft_exit_flag(0, exit_flag, data));
}
