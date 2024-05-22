/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:57:06 by bde-souz          #+#    #+#             */
/*   Updated: 2024/05/22 14:39:51 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int get_value(char *buffer, int i, t_data *data)
{
	int	y;

	y = 0;
	while(buffer[i] && !(buffer[i] >= 7 && buffer[i] <= 32))
		data->token->value[y++] = buffer[i++];
	return (i);
}

int	get_flags(char *buffer, int i, t_data *data)
{
	int y;

	y = 0;
	while(buffer[i] && !(buffer[i] >= 7 && buffer[i] <= 32))
	{
		if(buffer[i] == '-') //
		{
			while(buffer[i] && !(buffer[i] >= 7 && buffer[i] <= 32))
				data->token->flag[y++] = buffer[i++];
		}
		else
			i++;
	}
	return (i);
}

int	get_command(char *buffer, t_data *data)
{
	int i;
	int y;

	y = 0;
	i = 0;

	while(buffer[i] >= 7 && buffer[i] <= 32) // PULAR ESPACOS
		i++;
	while(buffer[i] && !(buffer[i] >= 7 && buffer[i] <= 32)) //PEGAR TODAS AS LETRAS
		data->token->command[y++] = buffer[i++];
	return (i);
}