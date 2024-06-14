/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:36:06 by bde-souz          #+#    #+#             */
/*   Updated: 2024/06/14 11:06:02 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	command_not_found(t_token *token)
{
	//asdasdasd: command not found

	ft_putstr_fd(token->str, 2);
	ft_putstr_fd(": command not found\n", 2);
	set_exit_code(127);
	
}

void	get_builtin(t_data *data)
{
	if(data->token->builtin == echo) // Se for echo
		get_echo(data->token->next); //Entra com o proximo <NODE>
	else if (data->token->builtin == pwd) // Se for pwd
		get_pwd(data->token);
	else if (data->token->builtin == cd)
		get_cd(data);
	else if (data->token->builtin == env)
		get_builtin_env(data);
	else if (data->token->builtin == n_exit)
		get_exit(data);
	else
		command_not_found(data->token); //#TODO Retirar daqui, por na func "use_command"
	
	//teste
	// char *test;
	// test = get_in_env(data->envp, "PWD");
	// printf("PWD atual: %s\n", test);
	// test = get_in_env(data->envp, "OLDPWD");
	// printf("OLDPWD atual: %s\n", test);
	//
}