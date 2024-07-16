/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:36:06 by bde-souz          #+#    #+#             */
/*   Updated: 2024/07/16 15:55:37 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_exit_flag(int exit_code, int exit_flag, t_data *data)
{
	if (exit_flag == 0) //flag 0 = data->exit_code
	{
		//ft_putstr_fd("Usando exit_flag_0 = data->exit_code ", 2); //DEBUG
		//ft_putnbr_fd(exit_code, 2);
		//ft_putstr_fd(" <--\n", 2);
		data->exit_code = exit_code;
	}
	else //flag 1 = signal
	{
		if (!data)
		exit(1);
		free_env(data->envp);
		free_token(data->token);
		if (data->tree)
			free_tree(data->tree);
		if (data->home)
			free(data->home);
		if (data->ex_)
			free(data->ex_);
		free(data);
		rl_clear_history();
		//exit(ex);
		exit(exit_code);
	}
}

void	command_not_found(char *str, t_data *data)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
	//ft_exit_flag(127, exit_flag, data);
	set_exit_code(127, data);
	clean(data, 127);
}


void	get_builtin(t_data *data, t_token *token, int flag)
{
	if (token->builtin == echo && !ft_strcmp(token->str, "echo"))
		get_echo(token->next, data, flag);
	else if (token->builtin == pwd && !ft_strcmp(token->str, "pwd"))
		get_pwd(token, data, flag);
	else if (token->builtin == cd && !ft_strcmp(token->str, "cd"))
		get_cd(data, token, flag);
	else if (token->builtin == env && !ft_strcmp(token->str, "env"))
		get_builtin_env(data, token, flag);
	else if (token->builtin == n_exit
		&& !ft_strcmp(token->str, "exit"))
		get_exit(data, token, flag);
	else if (token->builtin == export
		&& !ft_strcmp(token->str, "export"))
		get_export(data, token, flag);
	else if (token->builtin == unset
		&& !ft_strcmp(token->str, "unset"))
		get_unset(data, token, flag);
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
