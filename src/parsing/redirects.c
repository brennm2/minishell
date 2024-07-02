/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:25:35 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/06/26 16:37:47 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_token	*trim_redir(t_data *data, t_token *token)
{
	int	type;
	//t_token	*aux; #TODO func nao utilizada. Retirado devido as flags
	t_token	*aux_data;

	type = token->type;
	aux_data = data->token;
	while (aux_data->next != token)
		aux_data = aux_data->next;
	aux_data->next = token->next;
	aux_data->next->type = type;
	free(token);
	return (aux_data->next);
}

void	after_reds(t_data *data)
{
	t_token	*token_aux;

	token_aux = data->token;
	while (token_aux)
	{
		if (token_aux->type == redin || token_aux->type == redout || \
		token_aux->type == append || token_aux->type == here_doc)
			token_aux = trim_redir(data, token_aux);
		token_aux = token_aux->next;
	}
}
