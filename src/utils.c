/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:29:49 by bde-souz          #+#    #+#             */
/*   Updated: 2024/05/21 16:15:39 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"


void	init_command(t_commands *command, char *buffer)
{
	command->command = ft_calloc(1, (ft_strlen(buffer) + 1));
	command->value = ft_calloc(1, (ft_strlen(buffer) + 1));
	command->type = (t_types)malloc(sizeof(t_types));
	command->next = (t_commands *)malloc(sizeof(t_commands));
}

void init_data(t_data *data, char *buffer)
{
	data->commands = (t_commands *)malloc(sizeof(t_commands));
	data->envp = (t_envp *)malloc(sizeof(t_envp));
	data->next = (t_data *)(malloc(sizeof(t_data)));
	init_command(data->commands, buffer);
}


