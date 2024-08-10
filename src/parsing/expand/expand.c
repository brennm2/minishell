/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:29:01 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/08/10 17:20:12 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	expand_til(t_token *token, int i, char *home)
{
	char	*expanded;

	i++;
	if (token->str[i] == ' ' || token->str[i] == '/' || !token->str[i])
	{
		expanded = ft_calloc(sizeof(char), (i + 1));
		ft_strlcpy(expanded, token->str, i);
		if (home)
			expanded = ft_strjoin_ex(expanded, home);
		expanded = ft_strjoin_ex(expanded, token->str + i);
		free(token->str);
		token->str = expanded;
	}
}

void	erase_dollar_sign(t_token *token, int i)
{
	char	*str;

	str = ft_calloc(sizeof(char), (i + 1));
	ft_strlcpy(str, token->str, i);
	str = ft_strjoin_ex(str, token->str + i + 1);
	free(token->str);
	token->str = str;
}

bool	is_expand_2(t_token *token, t_data *data, int i)
{
	int	j;

	j = 0;
	if (token->str[i] == '$' && token->str[i + 1] && token->str[i + 1] \
		!= S_QUOTES && token->str[i + 1] != D_QUOTES)
	{
		is_expand_util(token, data, i, j);
		return (true);
	}
	if (token->str[i] == '$' && token->str[i + 1] && (token->str[i + 1] \
		== S_QUOTES || token->str[i + 1] == D_QUOTES) && \
		quote_status(token->str, i) == 0)
	{
		erase_dollar_sign(token, i);
		return (true);
	}
	return (false);
}

bool	is_expand(t_token *token, t_data *data)
{
	int	i;
	bool	flag;

	i = 0;
	flag = false;
	while (token->str[i])
	{
		if (token->str[i] == S_QUOTES && quote_status(token->str, i) == -1)
			i = deal_with_quotes(token, i);
		if (token->str[i] == '$' && token->str[i + 1] && token->str[i + 1] \
			!= ' ' && !ft_is_especial_2(token->str[i + 1]))
		{
			if (is_expand_2(token, data, i))
			{
				flag = true;
				continue ;
		}
		if (token->str[i] == '~' && i == 0 && quote_status(token->str, i) >= 0)
			expand_til(token, i, data->home);
		i++;
	}
	if (flag == true)
		split_token(token);
	return (flag);
}

t_token	*erase_token(t_data *data, t_token *token)
{
	t_token	*aux;
	t_token	*dead;

	aux = data->token;
	if (aux == token)
	{
		dead = aux;
		data->token = aux->next;
		free_token_redir(aux);
		return (data->token);
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
		while (token->str[i] && i != (ft_strlen(token->str) - 1) && token->str[i] == ' ')
			i++;
		if (i == (ft_strlen(token->str) - 1))
			return (true);
	}
	return (false);
}

void	expand(t_data *data)
{
	t_token	*token_aux;
	bool	flag;

	token_aux = data->token;
	while (token_aux)
	{
		flag = is_expand(token_aux, data);
		update_tokenize(token_aux);
		if (all_space_or_null(token_aux) && flag)
			token_aux = erase_token(data, token_aux);
		if (token_aux)
			token_aux = token_aux->next;
	}
	update_token(data);
}
