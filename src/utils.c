/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:29:49 by bde-souz          #+#    #+#             */
/*   Updated: 2024/05/15 16:38:13 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	init_command(t_command *command)
{
	command->command = ft_calloc(1,1);
	command->type = -1;
	//command->types = (t_types *)malloc(sizeof(t_types));
}

void init_data(t_data *data)
{
	data->command = (t_command *)malloc(sizeof(t_command));
	init_command(data->command);
}