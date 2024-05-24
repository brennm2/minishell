/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:14:09 by bde-souz          #+#    #+#             */
/*   Updated: 2024/05/24 16:59:45 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	free_token(t_token *token)
{
	//#TODO Terminar a func para dar clean no token por completo
	t_token *temp_token;
	
	while(token)
	{
		temp_token = token->next;
		token->str = NULL;
		free(token->str);
		//free(token->type);
		//free(token);
		free(token->next);
		token = temp_token;
	}
	printf("Lista limpa\n");
	
}

void	free_all(t_data *data)
{
	//#TODO Terminar a func de limpar toda as listas
	t_data *temp_data;
	
	if (data->token)
	{
		free_token(data->token);
	
	}
	while(data->next)
	{
		temp_data = data->next;
		free(data->envp);
		free(data->token);
		free(data->next);
		free(data);
		data = temp_data;
	}
}