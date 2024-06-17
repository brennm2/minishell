/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:14:09 by bde-souz          #+#    #+#             */
/*   Updated: 2024/06/12 18:51:22 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	free_token(t_token *token)
{
	t_token	*temp_token;
	
	while(token)
	{
		temp_token = token->next;
		free(token->str);
		free(token);
		token = temp_token;
	}
}

void	free_env(t_envp *envp)
{
	t_envp	*temp_envp;
	
	while(envp)
	{
		temp_envp = envp->next;
		free(envp->key);
		free(envp->value);
		free(envp);
		envp = temp_envp;
	}
}

void	ft_free_data(t_data *data, int option)
{
	t_data *temp_data;
	
	while(data)
	{
		temp_data = data->next;
		if (option == 0)
			free_token(data->token);
		if (option == 1)
		{
			free_token(data->token);
			free_env(data->envp);
			free(data);
		}
		data = temp_data;
	}
}
