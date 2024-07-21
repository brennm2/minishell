/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:14:09 by bde-souz          #+#    #+#             */
/*   Updated: 2024/07/21 14:48:38 by nsouza-o         ###   ########.fr       */
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
		token->str = NULL;
		if (token->exp)
			free(token->exp);
		free(token);
		token = NULL;
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
        envp->key = NULL;
        free(envp->value);
        envp->value = NULL;
        free(envp);
		envp = NULL;
        envp = temp_envp;
    }
}
void	free_data(t_data *data)
{
	if (data->home)
		free(data->home);
	data->home = NULL;
	if (data->ex_)
		free(data->ex_);
	//free(data->token);
	//free(data->envp);
	free(data);
	data = NULL;
}

void	ft_free_data(t_data *data, int option)
{
	t_data *temp_data;
	
	while(data)
	{
		temp_data = data->next;
		if (option >= 0)
			free_token(data->token);
		if (option >= 1)
		{
			free_token(data->token);
			free_env(data->envp);
			free(data);
		}
		data = temp_data;
	}
}

void	*ptr_free(char **ptr)
{	
	int i;

	i = 0;	
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (NULL);
}

