/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:29:49 by bde-souz          #+#    #+#             */
/*   Updated: 2024/06/03 16:29:21 by bde-souz         ###   ########.fr       */
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
	//data->envp = (t_envp *)ft_calloc(1, sizeof(t_envp));
	data->next = (t_data *)(ft_calloc(1, sizeof(t_data)));
	init_token(data->token, buffer);
}


