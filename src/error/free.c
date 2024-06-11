/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:14:09 by bde-souz          #+#    #+#             */
/*   Updated: 2024/06/03 16:27:50 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	free_token(t_token *token)
{
	t_token	*temp_token;
	t_token *temp_next_token;

	temp_token = token;
	while(temp_token)
	{
		temp_next_token = temp_token->next;
		free(temp_token->str);
		free(temp_token);
		temp_token = temp_next_token;
	}
}

void	ft_free_data(t_data *data, int option)
{
	t_data *temp_data;
	t_data *temp_next_data;

	temp_data = data;
	while(temp_data)
	{
		temp_next_data = temp_data->next;
		if (option >= 0)
			free_token(temp_data->token);
		if (option >= 1)
			free(temp_data);
		temp_data = temp_next_data;
	}
}

