/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:36:06 by bde-souz          #+#    #+#             */
/*   Updated: 2024/06/18 15:03:48 by bde-souz         ###   ########.fr       */
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
	if(data->token->builtin == echo && !ft_strcmp(data->token->str, "echo"))
		get_echo(data->token->next); //Entra com o proximo <NODE>
	else if (data->token->builtin == pwd && !ft_strcmp(data->token->str, "pwd"))
		get_pwd(data->token);
	else if (data->token->builtin == cd && !ft_strcmp(data->token->str, "cd"))
		get_cd(data);
	else if (data->token->builtin == env && !ft_strcmp(data->token->str, "env"))
		get_builtin_env(data);
	else if (data->token->builtin == n_exit
		&& !ft_strcmp(data->token->str, "exit"))
		get_exit(data);
	else
		command_not_found(data->token); //#TODO Verificar se isso pode ficar aqui

}
