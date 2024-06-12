/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:36:06 by bde-souz          #+#    #+#             */
/*   Updated: 2024/06/12 15:11:44 by bde-souz         ###   ########.fr       */
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
	
	//teste
	// char *test;
	// test = get_in_env(data->envp, "PWD");
	// printf("PWD atual: %s\n", test);
	// test = get_in_env(data->envp, "OLDPWD");
	// printf("OLDPWD atual: %s\n", test);
	//
}



// void	getPWD(t_data *data)
// {
// 	char PWD[PATH_MAX];
// 	getcwd(PWD, sizeof(PWD));
// 	printf("%s\n", PWD);
// 	free(data->token);
// }

// void	getCD(t_data *data)
// {
// 	printf("this is a cd\n");
// 	free(data->token);
// }

// void	getECHO(t_data *data)
// {
// 	t_token *temp_data;

// 	temp_data = data->token;

// 	while(data->token->value != NULL)
// 	{
// 		// se tiver -n
// 			//
// 		printf("%s ", data->token->value);
// 		data->token = data->token->next;
// 	}
// 	printf("\n");
// 	//free(data->command);
// }