/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_tokens_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:29:37 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/08/07 18:24:06 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	set_builtins(t_token *token, t_builtins	blt)
{
	token->type = builtin;
	token->builtin = blt;
}

void	after_pipe(t_data *data)
{
	t_token	*token_aux;

	token_aux = data->token;
	while (token_aux)
	{
		if (token_aux->type == is_pipe)
		{
			if (token_aux->next->type == string)
			{
				token_aux = token_aux->next;
				which_command(token_aux);
			}
		}
		token_aux = token_aux->next;
	}
}

void	is_red(t_token *token)
{
	if (!ft_strcmp(token->str, "<"))
		token->type = redin;
	else if (!ft_strcmp(token->str, ">"))
		token->type = redout;
	else if (!ft_strcmp(token->str, ">>"))
		token->type = append;
}

bool	is_red_or_pipe(t_token *token)
{
	if (token->type == redin || token->type == redout)
		return (true);
	if (token->type == append || token->type == here_doc)
		return (true);
	if (token->type == is_pipe)
		return (true);
	return (false);
}
