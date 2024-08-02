/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:57:06 by bde-souz          #+#    #+#             */
/*   Updated: 2024/08/02 18:01:04 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

t_token	*alloc_token(t_data *data)
{
	t_token *token_aux;
	
	if (!data->token)
	{
		data->token = ft_calloc(1, sizeof(t_token));
		token_aux = data->token;
	}
	else
	{
		token_aux = data->token;
		while (token_aux->next)
			token_aux = token_aux->next;
		token_aux->next = ft_calloc(1, sizeof(t_token));
		token_aux = token_aux->next;
	}
	return (token_aux);
}

int	save_substring(char *buffer, int size, int i, t_data *data)
{
	t_token *token_aux;
	int		j;
	
	j = 0;
	token_aux = alloc_token(data);
	token_aux->str = ft_calloc((size + 1), sizeof(char));
	while(j < size)
        token_aux->str[j++] = buffer[i++];
	token_aux->str[j] = '\0';
	return (i);
	/* int	i;

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
		start = check_for_string(buffer, end + 1); //Acha a proxima palavra
		i = start; // i fica igual ao inicio da palavra
		while (buffer[i] && !(buffer[i] >= 7 && buffer[i] <= 32)) // anda pela palavra ate achar espaco
			i++;
		end = i - 1; // end vai ser igual ao i
		init_next_token(data->token, end - start + 2); // Inicia o proximo token com o tamnho da string
		data->token = data->token->next;
	} */
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
	//t_token	*reset_index;
	int		i;
	
	//reset_index = data->token;
	i = 0;
	while(buffer[i])
	{
		if (buffer[i] && (buffer[i] >= 7 && buffer[i] <= 32))
			i = move_space(buffer, i);
		if (buffer[i] && !(buffer[i] >= 7 && buffer[i] <= 32))
		{
			i = move_without_quotes(buffer, i, data);
		}
		//printf("%c\n", buffer[i]);
	}
	//data->token = reset_index;
}
