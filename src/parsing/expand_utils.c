/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:03:08 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/07/03 19:06:31 by nsouza-o         ###   ########.fr       */
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

void	expansion_exit_code(t_token *token, int j, int i, char *exit_code)
{
	char	*expanded;

	expanded = ft_calloc(sizeof(char), (j + 1));
	ft_strlcpy(expanded, token->str, j + 1);
	expanded = ft_strjoin_ex(expanded, exit_code);
	expanded = ft_strjoin_ex(expanded, token->str + i + 2);
	free(exit_code);
	free(token->str);
	token->str = expanded;
}

void	is_expand_util(t_token *token, t_envp *envp, int i, int j)
{
	char	*exit_code;

	j = i;
	if (token->str[i + 1] == '?')
	{
		exit_code = ft_itoa(G_EXIT_CODE);
		expansion_exit_code(token, j, i, exit_code);
		//free(token->str);
		//token->str = exit_code;
		return ;
	}
	while (!ft_is_especial(token->str[++i]) && token->str[i])
		;
	check_env(token, envp, j, i);
}
