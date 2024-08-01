/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:16:52 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/08/01 21:13:57 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	erase_the_quote(t_token *token, int i)
{
	char	*unquote_str;
	
	if (i > 0)
	{
		unquote_str = ft_calloc(sizeof(char), i + 1);
		ft_strlcpy(unquote_str, token->str, i + 1);
	}
	else
		unquote_str = ft_strdup("");
	i++;
	unquote_str = ft_strjoin_ex(unquote_str, token->str + i);
	free(token->str);
	token->str = unquote_str;
}

int	deal_quotes(char *token, int i)
{
	char	quote;

	quote = token[i];
	while (token[++i] && token[i] != quote)
		;
	return (i);
}

void	unquote_token(t_token *token)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (token->str[i])
	{
		if ((token->str[i] == S_QUOTES || token->str[i] == D_QUOTES))
		{
			j = deal_quotes(token->str, i);
			erase_the_quote(token, i);
			erase_the_quote(token, j - 1);
			i = j - 1;
		}
		else
			i++;
	}
}

void	remove_quotes(t_data *data)
{
	t_token	*token_aux;

	token_aux = data->token;
	while (token_aux)
	{
		unquote_token(token_aux);
		token_aux = token_aux->next;
	}
}
