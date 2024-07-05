/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:25:35 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/07/05 11:56:23 by bde-souz         ###   ########.fr       */
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
	free(token);
	token = NULL;
}

t_token	*trim_redir(t_data *data, t_token *token)
{
	int	type;
	//t_token	*aux; #TODO func nao utilizada. Retirado devido as flags
	t_token	*aux_data;
	t_token	*dead_token; //Criada para guardar o token descartado

	type = token->type;
	aux_data = data->token;
	while (aux_data->next != token)
		aux_data = aux_data->next;
	dead_token = aux_data->next; // Atribui o valor do token que vai ser descartado
	aux_data->next = token->next;
	aux_data->next->type = type;
	free_token_redir(dead_token); //Limpa o token descartado
	//free(token);
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
