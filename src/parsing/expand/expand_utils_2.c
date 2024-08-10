/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 12:48:47 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/08/10 17:10:37 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

char	*erase_the_quote_ex(char *str, int i)
{
	char	*unquote_str;

	if (i > 0)
	{
		unquote_str = ft_calloc(sizeof(char), i + 1);
		ft_strlcpy(unquote_str, str, i + 1);
	}
	else
		unquote_str = ft_strdup("");
	i++;
	unquote_str = ft_strjoin_ex(unquote_str, str + i);
	free(str);
	return (unquote_str);
}

char	*unquote_str(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] == S_QUOTES || str[i] == D_QUOTES))
		{
			j = deal_quotes(str, i);
			str = erase_the_quote_ex(str, i);
			str = erase_the_quote_ex(str, j - 1);
			i = j - 1;
		}
		else
			i++;
	}
	return (str);
}

t_token	*split_token_2(t_token *token, char *str)
{
	t_token	*token_2;

	token_2 = ft_calloc(1, sizeof(t_token));
	token_2->str = ft_strdup(str);
	token->next = token_2;
	return (token_2);
}

void	split_token(t_token *token)
{
	t_token *token_next;
	char	*str;
	char	**str_split;
	int		i;
	
	i = 0;
	if (token->str[i] == D_QUOTES && token->str[i] != D_QUOTES)
		return ;
	str = ft_strdup(token->str);
	str = unquote_str(str);
	if (is_all_space(str))
	{
		free(str);
		return ;
	}
	token_next = token->next;
	str_split = ft_split(str, ' ');
	if (str_split[1] == NULL)
		return ;
	free(token->str);
	token->str = ft_strdup(str_split[0]);
	while (str_split[++i] != NULL)
	{
		token = split_token_2(token, str_split[i]);
	}
	token->next = token_next;
	free(str);
	ptr_free(str_split);
}

void	update_tokenize(t_token *token)
{
	if (token->type == command)
	{
		if (!ft_strncmp(token->str, "\"echo\"", 7))
			return (set_builtins(token, echo));
		else if (!ft_strncmp(token->str, "\"cd\"", 5))
			return (set_builtins(token, cd));
		else if (!ft_strncmp(token->str, "\"pwd\"", 6))
			return (set_builtins(token, pwd));
		else if (!ft_strncmp(token->str, "\"export\"", 8))
			return (set_builtins(token, export));
		else if (!ft_strncmp(token->str, "\"unset\"", 7))
			return (set_builtins(token, unset));
		else if (!ft_strncmp(token->str, "\"env\"", 5))
			return (set_builtins(token, env));
		else if (!ft_strncmp(token->str, "\"exit\"", 6))
			return (set_builtins(token, n_exit));
	}
}
