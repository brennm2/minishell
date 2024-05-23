/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:57:06 by bde-souz          #+#    #+#             */
/*   Updated: 2024/05/23 15:04:37 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"


int	move_space(char *buffer, int i) // FUNC RECEBE <BUFFER> E <I> E ANDA ATE ACHAR UMA OUTRA LETRA
{
	while(buffer[i] && (buffer[i] >= 7 && buffer[i] <= 32))
		i++;
	return(i);
}

void	create_node(t_data *data, char *buffer)
{
	data->token = data->token->next;
	init_token(data->token, buffer);
}

void	save_substring(char *buffer, int start, int end, t_data *data)
{
	int	i;

	i = 0;
	while(start <= end)
		data->token->str[i++] = buffer[start++];
	if(buffer[start] == D_QUOTES || S_QUOTES)
		start++;
	if(buffer[start])
	{
		data->token = data->token->next;
		init_token(data->token, buffer);
	}
		
}

int	move_without_quotes(char *buffer, int i, t_data *data)
{
	int start;

	start = i;
	while(buffer[i] && !(buffer[i] >= 7 && buffer[i] <= 32 
		|| buffer[i] == D_QUOTES ||  buffer[i] == S_QUOTES))
		i++;
	save_substring(buffer, start, (i - 1), data);
	return(i);
}


int	move_with_quotes(char *buffer, int i, int flag, t_data *data)
{
	int start;

	start = i;
	i++;
	while(buffer[i] && buffer[i] != flag)
		i++;
	if(!buffer[i])
	{
		
		ft_printf("ERROR, \n");
	}
	if (buffer[i] == flag)
		i++;
	save_substring(buffer, (start + 1), (i - 2), data);
	return(i);
}

void	get_split(char *buffer, t_data *data)
{
	t_token *reset_index;

	reset_index = data->token;
	
	int i;

	i = 0;
	while(buffer[i])
	{
		if (buffer[i] && (buffer[i] >= 7 && buffer[i] <= 32))
			i = move_space(buffer, i);
		// if (buffer[i] && !(buffer[i] >= 7 && buffer[i] <= 32))
		{
			if(buffer[i] == D_QUOTES)
				i = move_with_quotes(buffer, i, D_QUOTES, data);
			if (buffer[i] == S_QUOTES)
				i = move_with_quotes(buffer, i, S_QUOTES, data);
			// else
			if (buffer[i] && !(buffer[i] >= 7 && buffer[i] <= 32))
				i = move_without_quotes(buffer, i, data);
		}
	}
	data->token = reset_index;

	
	// int i;
	// int y;
	// t_token *reset_index;

	// i = 0;
	// y = 0;
	// reset_index = data->token;
	// i = move_space(buffer, i, data); // PULAR ESPACOS
	// while(buffer[i]) // ENQUANTO BUFFER EXISTIR
	// {
	// 	while(buffer[i] && !(buffer[i] >= 7 && buffer[i] <= 32)) // ENQUANTO BUFFER EXISTIR E FOR DIFERENTE DE ESPACO
	// 	{
	// 		//i = move_space(buffer, i, data);
	// 		data->token->str[y++] = buffer[i++];
	// 		if (buffer[i] && (buffer[i] >= 7 && buffer[i] <= 32)) // QUANDO ENCONTRAR ESPACO, ANDAR PARA O PROXIMO NODE
	// 		{
	// 			i = move_space(buffer, i, data);
	// 			if(buffer[i] == 0)
	// 				break;
	// 			data->token = data->token->next;
	// 			init_token(data->token, buffer); // ALOCAR ESPACO PARA O PROXIMO NODE
	// 			y = 0;
	// 		}
	// 	}
	// }
	// data->token = reset_index;
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