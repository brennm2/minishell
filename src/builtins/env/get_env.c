/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:13:12 by bde-souz          #+#    #+#             */
/*   Updated: 2024/08/09 11:48:19 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	env_error_invalid(t_data *data, t_token *token, int exit_flag)
{
	write(2, "env: invalid option -- ", 23);
	write(2, "'", 1);
	write(2, &token->next->str[1], 1);
	write(2, "'", 1);
	write(2, "\n", 1);
	ft_exit_flag(125, exit_flag, data);
}

void	env_error_option(t_data *data, t_token *token, int exit_flag)
{
	write(2, "env: ", 5);
	write(2, "'", 1);
	ft_putstr_fd(token->next->str, 2);
	write(2, "': No such file or directory", 29);
	write(2, "\n", 1);
	ft_exit_flag(127, exit_flag, data);
}

void	display_env(t_envp *envp, t_data *data, int exit_flag)
{
	while (envp)
	{
		if (envp->invisible == 0)
		{
			write(1, envp->key, ft_strlen(envp->key));
			write(1, "=", 1);
			write(1, envp->value, ft_strlen(envp->value));
			write(1, "\n", 1);
		}
		envp = envp->next;
	}
	return (ft_exit_flag(0, exit_flag, data));
}

void	get_builtin_env(t_data *data, t_token *token, int exit_flag)
{
	t_envp	*temp_env;

	temp_env = data->envp;
	if (token->next)
	{
		if (token->next->str[0] == '-' && token->next->str[1]
			&& token->next->type == string)
		{
			env_error_invalid(data, token, exit_flag);
			return ;
		}
	}
	if (token->next && token->next->type == string)
	{
		if (token->next->str[0] == '-')
			return (ft_exit_flag(0, exit_flag, data));
		env_error_option(data, token, exit_flag);
		return ;
	}
	else
		display_env(temp_env, data, exit_flag);
}
