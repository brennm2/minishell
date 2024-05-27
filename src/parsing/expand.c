/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:29:01 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/05/27 15:45:44 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	is_expand(t_token *token, t_data *data)
{
	bool	single_quotes;
	bool	doble_quotes;
	int		i;

	i = -1;
	while (token->str[++i])
	{
		if (token->str[i] == '"')
			
	}
}