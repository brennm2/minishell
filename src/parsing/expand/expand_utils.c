/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:03:08 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/08/09 11:07:36 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

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

void	expansion_digit(t_token *token, int j, int i)
{
	char	*expanded;

	expanded = ft_calloc(sizeof(char), (j + 1));
	ft_strlcpy(expanded, token->str, j + 1);
	if (token->str[i + 1] == '0')
		expanded = ft_strjoin_ex(expanded, "minishell");
	expanded = ft_strjoin_ex(expanded, token->str + i + 2);
	free(token->str);
	token->str = expanded;
}

void	expansion_dollar_sign(t_token *token, int j, int i, int pid)
{
	char	*expanded;
	char	*pid_char;

	pid_char = ft_itoa(pid);
	expanded = ft_calloc(sizeof(char), (j + 1));
	ft_strlcpy(expanded, token->str, j + 1);
	expanded = ft_strjoin_ex(expanded, pid_char);
	expanded = ft_strjoin_ex(expanded, token->str + i + 2);
	free(token->str);
	free(pid_char);
	token->str = expanded;
}

void	expansion_(t_data *data, t_token *token, int j)
{
	char	*expanded;

	expanded = ft_calloc(sizeof(char), (j + 1));
	ft_strlcpy(expanded, token->str, j + 1);
	if (!data->ex_)
		expanded = ft_strjoin_ex(expanded, "]");
	else
		expanded = ft_strjoin_ex(expanded, data->ex_);
	free(token->str);
	token->str = expanded;
}
