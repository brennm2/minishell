/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:36:06 by bde-souz          #+#    #+#             */
/*   Updated: 2024/06/13 16:56:59 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"


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
	
	//teste
	// char *test;
	// test = get_in_env(data->envp, "PWD");
	// printf("PWD atual: %s\n", test);
	// test = get_in_env(data->envp, "OLDPWD");
	// printf("OLDPWD atual: %s\n", test);
	//
}