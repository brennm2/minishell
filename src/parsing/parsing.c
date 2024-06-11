/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:57:06 by bde-souz          #+#    #+#             */
/*   Updated: 2024/06/11 16:16:44 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	save_substring(char *buffer, int start, int end, t_data *data)
{
	int	i;

	i = 0;
	while(start <= end)
	{
		data->token->str[i++] = buffer[start++];
	}
	if(buffer[start])
	{
		data->token = data->token->next;
		init_token(data->token, buffer);
	}
}

void	save_space(char *buffer, int start, t_data *data)
{
	int	i;

	i = 0;
	while(buffer[start] && buffer[start] >= 7 && buffer[start] <= 32)
		start++;
	data->token->str = ft_strdup(" ");
	if(buffer[start])
	{
		data->token = data->token->next;
		init_token(data->token, buffer);
	}
}

void	get_split(char *buffer, t_data *data)
{
	t_token	*reset_index;
	int		i;
	
	reset_index = data->token;
	i = 0;
	while(buffer[i])
	{
	//#TODO Definir em S_QUOTES nao permitir expandir e em D_QUOTES permitir (Finalizado?)
		if (buffer[i] && (buffer[i] >= 7 && buffer[i] <= 32))
		{
			i = move_space(buffer, i);
			//save_space(buffer, i, data);
		}
		
		// if(buffer[i] == D_QUOTES)
		// dquotes = 1;
		// 		i = move_with_quotes(buffer, i, D_QUOTES, data);
		// if (buffer[i] == S_QUOTES)
		// 		i = move_with_quotes(buffer, i, S_QUOTES, data);
		if (buffer[i] && !(buffer[i] >= 7 && buffer[i] <= 32))
		{
				i = move_without_quotes(buffer, i, data);		
		}
	}
	data->token = reset_index;
}
