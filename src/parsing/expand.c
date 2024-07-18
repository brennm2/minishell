/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:29:01 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/07/18 14:09:08 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	expansion(t_envp *envp, t_token *token, int j, int i)
{
	char	*expanded;

	expanded = ft_calloc(sizeof(char), (j + 1));
	ft_strlcpy(expanded, token->str, j + 1);
	if (envp)
		expanded = ft_strjoin_ex(expanded, envp->value);
	expanded = ft_strjoin_ex(expanded, token->str + i);
	free(token->str);
	token->str = expanded;
}

void	check_env(t_token *token, t_envp *env, int j, int i)
{
	char	*variable;
	int		size;
	t_envp	*env_aux;

	env_aux = env;
	size = i - j;
	variable = ft_calloc(sizeof(char), size + 1);
	if (!variable)
		exit(1);
	ft_strlcpy(variable, token->str + j + 1, (size));
	while (env_aux)
	{
		if (!ft_strncmp(variable, env_aux->key, size))
		{
			expansion(env_aux, token, j, i);
			free(variable);
			return ;
		}
		env_aux = env_aux->next;
	}
	expansion(NULL, token, j, i);
	free(variable);
}

void	expand_til(t_token *token, int i, char *home)
{
	char	*expanded;

	i++;
	if (token->str[i] == ' ' || token->str[i] == '/' || !token->str[i])
	{
		expanded = ft_calloc(sizeof(char), (i + 1));
		ft_strlcpy(expanded, token->str, i);
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
	== S_QUOTES || token->str[i + 1] == D_QUOTES) && quote_status(token->str, i) == 0)
	{
		erase_dollar_sign(token, i);
		return (true);
	}
	return (false);
}

void	is_expand(t_token *token, t_data *data)
{
	int	i;

	i = -1;
	while (token->str[++i])
	{
		if (token->str[i] == S_QUOTES && quote_status(token->str, i) == -1)
			i = deal_with_quotes(token, i);
		if (token->str[i] == '$' && token->str[i + 1])
		{
			if (is_expand_2(token, data, i))
			{
				i = -1;
				continue ;
			}
		}
		if (token->str[i] == '~' && i == 0 && quote_status(token->str, i) >= 0)
			expand_til(token, i, data->home);
	}
}

void	expand(t_data *data)
{
	t_token	*token_aux;

	token_aux = data->token;
	while (token_aux)
	{
		is_expand(token_aux, data->envp, data->home, data);
		token_aux = token_aux->next;
	}
}
