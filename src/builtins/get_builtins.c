/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:36:06 by bde-souz          #+#    #+#             */
/*   Updated: 2024/05/20 13:29:48 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"


void	getPWD(t_data *data)
{
	char PWD[PATH_MAX];
	getcwd(PWD, sizeof(PWD));
	printf("%s\n", PWD);
	free(data->command);
}

void	getCD(t_data *data)
{
	printf("this is a cd\n");
	free(data->command);
}

void	getECHO(t_data *data)
{
	t_command *temp_data;

	temp_data = data->command;

	while(data->command->value != NULL)
	{
		printf("%s ", data->command->value);
		data->command = data->command->next;
		// if(!data->command->next)
		// 	printf("\n");
	}
	printf("\n");
	//free(data->command);
}