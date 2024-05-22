/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:57:06 by bde-souz          #+#    #+#             */
/*   Updated: 2024/05/22 17:06:36 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"


int	move_space(char *buffer, int i) // FUNC RECEBE <BUFFER> E <I> E ANDA ATE ACHAR UMA OUTRA LETRA
{
	while(buffer[i] && (buffer[i] >= 7 && buffer[i] <= 32
		|| buffer[i] == S_QUOTES || buffer[i] == D_QUOTES))
		i++;
	return(i);
}


void	get_split(char *buffer, t_data *data)
{
	int i;
	int y;
	t_token *reset_index;

	i = 0;
	y = 0;
	reset_index = data->token;
	i = move_space(buffer, i); // PULAR ESPACOS
	while(buffer[i]) // ENQUANTO BUFFER EXISTIR
	{
		while(buffer[i] && !(buffer[i] >= 7 && buffer[i] <= 32)) // ENQUANTO BUFFER EXISTIR E FOR DIFERENTE DE ESPACO
		{
			data->token->str[y++] = buffer[i++];
			if (buffer[i] && (buffer[i] >= 7 && buffer[i] <= 32)) // QUANDO ENCONTRAR ESPACO, ANDAR PARA O PRIXIMO NODE
			{
				data->token = data->token->next;
				init_token(data->token, buffer); // ALOCAR ESPACO PARA O PROXIMO NODE
				i = move_space(buffer, i);
				y = 0;
			}
		}
	}
	data->token = reset_index;
}

// int get_value(char *buffer, int i, t_data *data)
// {
// 	int	y;

// 	y = 0;
// 	while(buffer[i] && !(buffer[i] >= 7 && buffer[i] <= 32))
// 		data->token->value[y++] = buffer[i++];
// 	return (i);
// }

// int	get_flags(char *buffer, int i, t_data *data)
// {
// 	int y;

// 	y = 0;
// 	while(buffer[i] && !(buffer[i] >= 7 && buffer[i] <= 32))
// 	{
// 		if(buffer[i] == '-') //
// 		{
// 			while(buffer[i] && !(buffer[i] >= 7 && buffer[i] <= 32))
// 				data->token->flag[y++] = buffer[i++];
// 		}
// 		else
// 			i++;
// 	}
// 	return (i);
// }

// int	get_command(char *buffer, t_data *data)
// {
// 	int i;
// 	int y;

// 	y = 0;
// 	i = 0;

// 	while(buffer[i] >= 7 && buffer[i] <= 32) // PULAR ESPACOS
// 		i++;
// 	while(buffer[i] && !(buffer[i] >= 7 && buffer[i] <= 32)) //PEGAR TODAS AS LETRAS
// 		data->token->command[y++] = buffer[i++];
// 	return (i);
// }