/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:29:49 by bde-souz          #+#    #+#             */
/*   Updated: 2024/05/31 16:12:54 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"


void	init_token(t_token *token, char *buffer)
{
	token->str = ft_calloc(1, ft_strlen(buffer) + 1);
	//token->type = (t_types)malloc(sizeof(t_types));
	token->next = (t_token *)ft_calloc(1, sizeof(t_token));
}

void init_data(t_data *data, char *buffer)
{
	data->token = (t_token *)ft_calloc(1, sizeof(t_token));
	data->envp = (t_envp *)ft_calloc(1, sizeof(t_envp));
	data->next = (t_data *)(ft_calloc(1, sizeof(t_data)));
	init_token(data->token, buffer);
}


