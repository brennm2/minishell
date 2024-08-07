/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:29:49 by bde-souz          #+#    #+#             */
/*   Updated: 2024/08/07 09:55:23 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void	init_next_token(t_token *token, int len)
{
	token->next = (t_token *)ft_calloc(1, sizeof(t_token));
	token->next->str = ft_calloc(sizeof(char *), len + 1);
}

void	init_token(t_token *token, char *buffer)
{
	token->str = ft_calloc(1, ft_strlen(buffer) + 1);
}

void init_data(t_data *data, char *buffer)
{
	data->token = (t_token *)ft_calloc(1, sizeof(t_token));
	init_token(data->token, buffer);
}

void	*safe_calloc(size_t bytes, size_t n, t_data *data)
{
	void	*var;
	
	var = ft_calloc(n, bytes);
	if (!var)
	{
		print_error("Malloc error.", 1, data);
		clean(data, 1);
	}
	return (var);
}
