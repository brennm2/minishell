/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:25:35 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/07/17 19:31:02 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"


// t_token	*trim_redir(t_data *data, t_token *token)
// {
// 	int	type;
// 	//t_token	*aux; #TODO func nao utilizada. Retirado devido as flags
// 	t_token	*aux_data;

// 	type = token->type;
// 	aux_data = data->token;
// 	while (aux_data->next != token)
// 		aux_data = aux_data->next;
// 	aux_data->next = token->next;
// 	aux_data->next->type = type;
// 	free(token);
// 	return (aux_data->next);
// }

void	free_token_redir(t_token *token)
{
	free(token->str);
	token->str = NULL;
	if (token->exp)
		free(token->exp);
	free(token);
	token = NULL;
}

t_token	*trim_first_redir(t_data *data, t_token *token)
{
	t_token	*head;
	t_token	*dead_token;
	
	head = token->next;
	token->next->type = token->type;
	dead_token = token;
	data->token = head;
	free_token_redir(dead_token);
	return (data->token);
}

t_token	*trim_redir(t_data *data, t_token *token)
{
	int	type;
	t_token	*aux_data;
	t_token	*dead_token;

	type = token->type;
	aux_data = data->token;
	if (aux_data == token)
	{
		aux_data = trim_first_redir(data, token);
		return (aux_data);
	}
	while (aux_data->next != token)
		aux_data = aux_data->next;
	dead_token = aux_data->next;
	aux_data->next = token->next;
	aux_data->next->type = type;
	free_token_redir(dead_token);
	return (aux_data->next);
}

void	after_reds(t_data *data)
{
	t_token	*token_aux;

	token_aux = data->token;
	while (token_aux)
	{
		if (token_aux->type == redin || token_aux->type == redout || \
		token_aux->type == append)
			token_aux = trim_redir(data, token_aux);
		token_aux = token_aux->next;
	}
}
