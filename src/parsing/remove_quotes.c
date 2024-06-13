/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:16:52 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/06/13 20:46:02 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	erase_the_quote(t_token *token, int i)
{
	char *unquote_str;

	unquote_str = ft_calloc(sizeof(char), i + 1);
	ft_strlcpy(unquote_str, token->str, i + 1);
	i++;
	unquote_str = ft_strjoin_ex(unquote_str, token->str + i);
	free(token->str);
	token->str = unquote_str;
}

void	unquote_token(t_token *token)
{
	int	i;
	int j;
	char	*dup;

	i = -1;
	j = -1;
	dup = ft_strdup(token->str);
	while (token->str[++i])
	{
		++j;
		if (token->str[i] == S_QUOTES || token->str[i] == D_QUOTES)
		{
			if (quote_status(dup, j) < 0);
				continue;
			erase_the_quote(token, i);
			i--;	
		}
	}
	free(dup);
}

void	remove_quotes(t_data *data)
{
	t_token *token_aux;

	token_aux = data->token;
	while (token_aux->next)
	{
		unquote_token(token_aux);
		token_aux = token_aux->next;
	}
}