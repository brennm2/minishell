/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:57:06 by bde-souz          #+#    #+#             */
/*   Updated: 2024/05/21 16:05:12 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	get_command(char *buffer, t_data *data)
{
	int i;
	int y;

	y = 0;
	i = 0;

	while(buffer[i] >= 7 && buffer[i] <= 32)
		i++;
	while(buffer[i] && !(buffer[i] >= 7 && buffer[i] <= 32))
		data->commands->command[i] = buffer[i++];
	return (i);
}