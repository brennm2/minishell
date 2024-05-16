/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:29:49 by bde-souz          #+#    #+#             */
/*   Updated: 2024/05/16 15:36:25 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"


void	init_command(t_command *command, char *buffer)
{
	command->command = ft_calloc(1, (ft_strlen(buffer) + 1));
	command->value = ft_calloc(1, (ft_strlen(buffer) + 1));
	command->next = malloc(sizeof(t_command));
}

void init_data(t_data *data, char *buffer)
{
	data->command = (t_command *)malloc(sizeof(t_command));
	init_command(data->command, buffer);
}