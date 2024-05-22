/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:29:49 by bde-souz          #+#    #+#             */
/*   Updated: 2024/05/22 12:12:23 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"


void	init_command(t_token *token, char *buffer)
{
	token->command = ft_calloc(1, (ft_strlen(buffer) + 1));
	token->value = ft_calloc(1, (ft_strlen(buffer) + 1));
	token->flag = ft_calloc(1, (ft_strlen(buffer) + 1));
	token->type = (t_types)malloc(sizeof(t_types));
	token->next = (t_token *)malloc(sizeof(t_token));
}

void init_data(t_data *data, char *buffer)
{
	data->token = (t_token *)malloc(sizeof(t_token));
	data->envp = (t_envp *)malloc(sizeof(t_envp));
	data->next = (t_data *)(malloc(sizeof(t_data)));
	init_command(data->token, buffer);
}


