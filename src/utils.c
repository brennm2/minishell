/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:29:49 by bde-souz          #+#    #+#             */
/*   Updated: 2024/06/11 16:48:27 by nsouza-o         ###   ########.fr       */
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

void	init_token(t_token *token, char *buffer)
{
	token->str = ft_calloc(1, ft_strlen(buffer) + 1);
	//token->type = (t_types)malloc(sizeof(t_types));
	token->next = (t_token *)ft_calloc(1, sizeof(t_token));
}

void init_data(t_data *data, char *buffer)
{
	data->token = (t_token *)ft_calloc(1, sizeof(t_token));
	//data->envp = (t_envp *)ft_calloc(1, sizeof(t_envp));
	data->next = (t_data *)(ft_calloc(1, sizeof(t_data)));
	init_token(data->token, buffer);
}


