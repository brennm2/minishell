/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:56:26 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/08/14 16:23:42 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

t_token	*erase_token(t_data *data, t_token *token)
{
	t_token	*aux;
	t_token	*dead;

	aux = data->token;
	if (token->type == redin || token->type == redout || token->type == append \
		|| token->type == here_doc)
		return (token);
	if (aux == token)
	{
		dead = aux;
		data->token = aux->next;
		return (free_token_redir(aux), data->token);
	}
	while (aux)
	{
		if (aux->next == token)
		{
			dead = token;
			aux->next = token->next;
			free_token_redir(dead);
			break ;
		}
		aux = aux->next;
	}
	return (aux);
}

bool	all_space_or_null(t_token *token)
{
	size_t	i;

	i = 1;
	if (token->str[0] && token->str[0] == '\"')
	{
		while (token->str[i] && i != (ft_strlen(token->str) - 1) \
			&& token->str[i] == ' ')
			i++;
		if (i == (ft_strlen(token->str) - 1))
			return (true);
	}
	return (false);
}

int	have_dquotes(t_token *token)
{
	if (token->str[0] == D_QUOTES
		&& token->str[ft_strlen(token->str) - 1] == D_QUOTES)
		return (1);
	return (0);
}

bool	have_spaces(t_token *token)
{
	int	i;

	i = -1;
	while (token->str[++i])
	{
		if (token->str[i] == ' ')
			return (true);
	}
	return (false);
}
