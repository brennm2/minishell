/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:36:06 by bde-souz          #+#    #+#             */
/*   Updated: 2024/07/12 11:43:14 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_exit_flag(int exit_code, int exit_flag, t_data *data)
{
	if (exit_flag == 0) //flag 0 = data->exit_code
	{
		ft_putstr_fd("Usando exit_flag_0 = data->exit_code ", 2); //DEBUG
		ft_putnbr_fd(exit_code, 2);
		ft_putstr_fd(" <--\n", 2);
		data->exit_code = exit_code;
	}
	else //flag 1 = signal
	{
		ft_putstr_fd("Usando exit_flag_1 = exit: ", 2); //DEBUG
		ft_putnbr_fd(exit_code, 2);
		ft_putstr_fd(" <--\n", 2);
		exit(exit_code);
	}
}

void	command_not_found(t_token *token, t_data *data)
{
	ft_putstr_fd(token->str, 2);
	ft_putstr_fd(": command not found\n", 2);
	//ft_exit_flag(127, exit_flag, data);
	set_exit_code(127, data);
	clean(data, 127);
}


void	get_builtin(t_data *data, t_token *token, int flag)
{
	//flag 0 = data->exit_code / flag = 1 signal
	if (data->token->builtin == echo && !ft_strcmp(data->token->str, "echo"))
		get_echo(token->next, data, flag);
	else if (data->token->builtin == pwd && !ft_strcmp(data->token->str, "pwd"))
		get_pwd(token, data, flag);
	else if (data->token->builtin == cd && !ft_strcmp(data->token->str, "cd"))
		get_cd(data, token, flag);
	else if (data->token->builtin == env && !ft_strcmp(data->token->str, "env"))
		get_builtin_env(data, token, flag);
	else if (token->builtin == n_exit
		&& !ft_strcmp(token->str, "exit"))
		get_exit(data, token);
	else if (data->token->builtin == export
		&& !ft_strcmp(data->token->str, "export"))
		get_export(data, token, flag);
	else if (data->token->builtin == unset
		&& !ft_strcmp(data->token->str, "unset"))
		get_unset(data);
	/* else
		command_not_found(data->token); */
}

// void	get_builtin(t_data *data, t_token *token)
// {
// 	if (data->token->builtin == echo && !ft_strcmp(data->token->str, "echo"))
// 		get_echo(token->next, data);
// 	else if (data->token->builtin == pwd && !ft_strcmp(data->token->str, "pwd"))
// 		get_pwd(token);
// 	else if (data->token->builtin == cd && !ft_strcmp(data->token->str, "cd"))
// 		get_cd(data);
// 	else if (data->token->builtin == env && !ft_strcmp(data->token->str, "env"))
// 		get_builtin_env(data);
// 	else if (data->token->builtin == n_exit
// 		&& !ft_strcmp(data->token->str, "exit"))
// 		get_exit(data);
// 	else if (data->token->builtin == export
// 		&& !ft_strcmp(data->token->str, "export"))
// 		get_export(data);
// 	else if (data->token->builtin == unset
// 		&& !ft_strcmp(data->token->str, "unset"))
// 		get_unset(data);
// 	/* else
// 		command_not_found(data->token); */
// }
