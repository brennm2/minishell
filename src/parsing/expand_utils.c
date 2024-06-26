/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:03:08 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/06/21 19:03:41 by nsouza-o         ###   ########.fr       */
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

void	is_expand_util(t_token *token, t_envp *envp, int i, int j)
{
	j = i;
	if (token->str[i + 1] == '?')
	{
		free(token->str);
		token->str = ft_strdup(ft_itoa(G_EXIT_CODE));
		return ;
	}
	while (!ft_is_especial(token->str[++i]) && token->str[i])
		;
	check_env(token, envp, j, i);
}
