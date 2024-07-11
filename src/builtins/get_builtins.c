/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:36:06 by bde-souz          #+#    #+#             */
/*   Updated: 2024/07/11 12:05:27 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	command_not_found(t_token *token, t_data *data)
{
	ft_putstr_fd(token->str, 2);
	ft_putstr_fd(": command not found\n", 2);
	set_exit_code(127, data);
	clean(data, 127);
}


void	get_builtin(t_data *data, t_token *token)
{
	if (data->token->builtin == echo && !ft_strcmp(data->token->str, "echo"))
		get_echo(token->next, data);
	else if (data->token->builtin == pwd && !ft_strcmp(data->token->str, "pwd"))
		get_pwd(token, data);
	else if (data->token->builtin == cd && !ft_strcmp(data->token->str, "cd"))
		get_cd(data);
	else if (data->token->builtin == env && !ft_strcmp(data->token->str, "env"))
		get_builtin_env(data);
	else if (token->builtin == n_exit
		&& !ft_strcmp(token->str, "exit"))
		get_exit(data, token);
	else if (data->token->builtin == export
		&& !ft_strcmp(data->token->str, "export"))
		get_export(data);
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
