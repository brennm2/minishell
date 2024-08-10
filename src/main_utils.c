/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:40:13 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/08/10 16:12:28 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	have_pipe(t_data *data)
{
	t_token	*token_aux;

	token_aux = data->token;
	while (token_aux)
	{
		if (token_aux->type == is_pipe)
		{
			data->flag = 1;
			return ;
		}
		token_aux = token_aux->next;
	}
	data->flag = 0;
}

void	search_command(char *buffer, t_data *data)
{
	buffer = check_spaces(buffer);
	get_split(buffer, data);
	free(buffer);
}

void	set_ex_(t_data *data)
{
	t_token	*aux;

	aux = data->token;
	while (aux)
	{
		if (data->ex_)
			free(data->ex_);
		data->ex_ = ft_strdup(aux->str);
		if (aux->next && is_red_or_pipe(aux->next))
			break ;
		aux = aux->next;
	}
}

bool	is_red_bool(t_token *token)
{
	if (token->type == redin)
		return (true);
	else if (token->type == redout)
		return (true);
	else if (token->type == append)
		return (true);
	return (false);
}

void	update_token(t_data *data)
{
	t_token	*token_aux;
	t_token	*dead;

	token_aux = data->token;
	if (!token_aux)
		return ;
	if (token_aux->str[0] == '\0' && !is_red_bool(token_aux))
	{
		data->token = token_aux->next;
		free_token_redir(token_aux);
		if (data->token && data->token->type == string)
			which_command(data->token);
		return ;
	}
	while (token_aux)
	{
		if (token_aux->next && token_aux->next->str[0] == '\0' && \
			token_aux->next->type == string)
		{
			dead = token_aux->next;
			token_aux->next = token_aux->next->next;
			free_token_redir(dead);
		}
		token_aux = token_aux->next;
	}
}
