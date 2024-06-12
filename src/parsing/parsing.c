/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:57:06 by bde-souz          #+#    #+#             */
/*   Updated: 2024/06/12 11:58:03 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	check_for_string(char *buffer, int start)
{
	while(buffer[start])
	{
		if (buffer[start] && (buffer[start] >= 7 && buffer[start] <= 32))
		{
			start++;
		}
		else
			return (start);
	}
	return (start);
}

void	save_substring(char *buffer, int start, int end, t_data *data)
{
	int	i;

	i = 0;
	while(start <= end)
		data->token->str[i++] = buffer[start++];
	if(buffer[start] == D_QUOTES || buffer[start] == S_QUOTES)
		start++;
	if(buffer[check_for_string(buffer, start)])
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
	if(buffer[check_for_string(buffer, start)])
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
	//#TODO Veriicar echo "abc"a
	
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
