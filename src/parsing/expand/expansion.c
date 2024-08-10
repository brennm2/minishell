/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:34:44 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/08/10 11:59:17 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	expansion(t_envp *envp, t_token *token, int j, int i)
{
	char	*expanded;

	expanded = ft_calloc(sizeof(char), (j + 2));
	if (!token->exp)
		token->exp = ft_strdup(token->str);
	ft_strlcpy(expanded, token->str, j + 1);
	expanded = ft_strjoin_ex(expanded, "\"");
	if (envp)
		expanded = ft_strjoin_ex(expanded, envp->value);
	expanded = ft_strjoin_ex(expanded, "\"");
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

void	expansion_special(t_token *token, int j)
{
	char	*expanded;

	expanded = ft_calloc(sizeof(char), (j + 1));
	ft_strlcpy(expanded, token->str, j + 1);
	expanded = ft_strjoin_ex(expanded, token->str + j + 2);
	free(token->str);
	token->str = expanded;
}

bool	is_expand_util_2(t_token *token, t_data *data, int i, int j)
{
	if (token->str[i + 1] == '$')
	{
		expansion_dollar_sign(token, j, i, data->pid);
		return (true);
	}
	if (ft_isdigit(token->str[i + 1]))
	{
		expansion_digit(token, j, i);
		return (true);
	}
	if (token->str[i + 1] == '_' && !token->str[i + 2])
	{
		expansion_(data, token, j);
		return (true);
	}
	if (ft_is_especial(token->str[i + 1]))
	{
		expansion_special(token, j);
		return (true);
	}
	return (false);
}

void	is_expand_util(t_token *token, t_data *data, int i, int j)
{
	char	*exit_code;

	j = i;
	if (token->str[i + 1] == '?')
	{
		exit_code = ft_itoa(data->exit_code);
		expansion_exit_code(token, j, i, exit_code);
		return ;
	}
	if (is_expand_util_2(token, data, i, j))
		return ;
	while (!ft_is_especial(token->str[++i]) && token->str[i] && \
		token->str[i] != 32)
		;
	check_env(token, data->envp, j, i);
}
