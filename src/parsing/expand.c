/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:41:10 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/06/14 16:05:23 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	deal_with_quotes(t_token *token, int i)
{	
	if (token->str[i] == S_QUOTES)
	{
		i++;
		while (token->str[i] != S_QUOTES)
			i++;
	}
	return (i);
}

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
	char *variable;
	int size;
	t_envp *env_aux;

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

void	is_expand(t_token *token, t_envp *envp)
{
	int i;
	int j;

	i = -1;
	while (token->str[++i])
	{
		if (token->str[i] == S_QUOTES && quote_status(token->str, i) == -1)
			i = deal_with_quotes(token, i);
		if (token->str[i] == '$' && token->str[i + 1] && token->str[i + 1] != S_QUOTES && token->str[i + 1] != D_QUOTES)
		{
			j = i;
			while (!ft_is_especial(token->str[++i]) && token->str[i])
				;
			check_env(token, envp, j, i);
			i = -1;
		}
	}
}

void	expand(t_data *data)
{
	t_token *token_aux;

	token_aux = data->token;
	while (token_aux->next)
	{
		is_expand(token_aux, data->envp);
		token_aux = token_aux->next;
	}
}
