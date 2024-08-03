/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:57:06 by bde-souz          #+#    #+#             */
/*   Updated: 2024/08/03 14:50:08 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

int	find_token_end(char *buffer, int i)
{
	int	start;

	start = i;
	if (buffer[i] && (buffer[i] == S_QUOTES || buffer[i] == D_QUOTES))
		while (buffer[++i] && buffer[i] != buffer[start])
			;
	else
		while (buffer[++i] && !(buffer[i] >= 7 && buffer[i] <= 32))
			;
	return (i);
}

void	save_substring(char *buffer, int start, int end, t_data *data)
{
	int	i;

	i = 0;
	while(start <= end)
	{
		data->token->str[i] = buffer[start++];
		i++;
	}
	if(buffer[start] == D_QUOTES || buffer[start] == S_QUOTES)
		start++;
	if(buffer[check_for_string(buffer, start)])
	{
		start = check_for_string(buffer, end + 1);
		i = start;
		i = find_token_end(buffer, i);
		end = i;
		init_next_token(data->token, end - start + 2);
		data->token = data->token->next;
	}
}

void	save_space(char *buffer, int start, t_data *data)
{
	while(buffer[start] && buffer[start] >= 7 && buffer[start] <= 32)
		start++;
	if(buffer[check_for_string(buffer, start)])
	{
		data->token = data->token->next;
		init_token(data->token, buffer);
	}
}
void	new_data(t_data *data, t_token *token)
{
	t_data	*newdata;

	newdata = ft_calloc(1, sizeof(t_data));
	newdata->envp = data->envp;
	newdata->token = token;
	newdata->next = NULL;
	data->next = newdata;
}

void	pipe_split(t_data *data)
{
	t_token	*aux;
	t_token	*token_aux;
	t_data *data_aux;
	
	data_aux = data;
	token_aux = data->token;
	while (token_aux->str)
	{
		if (!ft_strcmp(token_aux->str, "|"))
		{
			aux = token_aux->next;
			token_aux->next = NULL;
			new_data(data, aux);
			token_aux = data_aux->next->token;
		}
		else
			token_aux = token_aux->next;
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
		if (buffer[i] && (buffer[i] >= 7 && buffer[i] <= 32))
			i = move_space(buffer, i);
		if (buffer[i] && !(buffer[i] >= 7 && buffer[i] <= 32))
		{
				i = move_without_quotes(buffer, i, data);
		}
	}
	data->token = reset_index;
}
