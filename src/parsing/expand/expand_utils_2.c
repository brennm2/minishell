/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 12:48:47 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/08/10 13:04:57 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

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
