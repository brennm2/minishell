/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:57:34 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/07/03 16:33:19 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

bool	nbr_pipes(t_data *data)
{
	t_token *token_aux;
	
	token_aux = data->token;
	while (token_aux)
	{
		if (token_aux->type == is_pipe)
			return (true);
		token_aux = token_aux->next;
	}
	return (false);
}

t_token	*pipe_separator(t_data *data, t_token *token)
{
	t_token *new_first;
	t_token *token_aux;
	t_data	*new_data;
	
	new_data = ft_calloc(1, sizeof(t_data));
	token_aux = token->next;
	new_first = token->next->next;
	token->next = NULL;
	free(token_aux);
	new_data->envp = data->envp;
	new_data->token = new_first;
	new_data->home = data->home;
	new_data->next = NULL;
	data->next = new_data;
	return (new_first);	
}

void	split_pipes(t_data *data)
{
	t_data	*first;
	t_token *token_aux;
	
	first = data;
	token_aux = data->token;
	while (token_aux)
	{
		if (token_aux->next && token_aux->next->type == is_pipe)
			token_aux = pipe_separator(data, token_aux);
		else
			token_aux = token_aux->next;
	}
}

void	debbug_list_data(t_data *data)
{
	while (data)
	{
		debug_print_list(data);
		data = data->next;
	}
}

void	execution_pipes(t_data *data)
{
	split_pipes(data);
	//debbug_list_data(data);
}