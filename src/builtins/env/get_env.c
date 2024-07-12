/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:13:12 by bde-souz          #+#    #+#             */
/*   Updated: 2024/07/12 11:12:57 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	env_error_invalid(t_data *data, int exit_flag)
{
	write(2, "env: invalid option -- ", 23);
	write(2, "'", 1);
	write(2, &data->token->next->str[1], 1);
	write(2, "'", 1);
	write(2, "\n", 1);
	ft_exit_flag(127, exit_flag, data);
}

void	env_error_option(t_data *data, int exit_flag)
{
	write(2, "env: ", 5);
	write(2, "'", 1);
	write(2, data->token->next->str, ft_strlen(data->token->next->str));
	write(2, "': No such file or directory", 29);
	write(2, "\n", 1);
	ft_exit_flag(127, exit_flag, data);
}

void	display_env(t_envp *envp, t_data *data, int exit_flag)
{
	if (get_in_env(envp, "PATH") == NULL)
	{
		ft_putstr_fd("minishell: env: No such file or directory\n", 2);
		return (ft_exit_flag(127, exit_flag, data));
	}
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
	if (token->next) // Se for "env ..."
	{
		if (token->next->str[0] == '-' && token->next->str[1] && token->next->type == string) //Se for Option "-n"
		{
			env_error_invalid(data, exit_flag);
			return ;
		}
	}
	if (token->next && token->next->type == string) // Se for "env ..."
	{
		if (token->next->str[0] == '-') // Se for somente "-", retornar sem fazer nada
			return (ft_exit_flag(0, exit_flag, data));
		env_error_option(data, exit_flag);
		return ;
	}
	else //Se nenhuma dessas condicoes foi atendida...
		display_env(temp_env, data, exit_flag); // Mostra a lista de env
}
