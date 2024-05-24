/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:36:06 by bde-souz          #+#    #+#             */
/*   Updated: 2024/05/24 14:57:02 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"


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