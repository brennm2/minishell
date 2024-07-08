/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:14:09 by bde-souz          #+#    #+#             */
/*   Updated: 2024/07/08 16:15:29 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	free_token(t_token *token)
{
	t_token	*temp_token;
	
	while(token)
	{
		temp_token = token->next;
		if (token->str)
		free(token->str);
		token->str = NULL;
		free(token);
		token = NULL;
		//token = NULL;
		token = temp_token;
	}
	//free(temp_token);
	//printf("%s", token->str);
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
	free(data->home);
	data->home = NULL;
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
		// free(data->envp);
		// data->envp = NULL;
		// free(data->home);
		// data->home = NULL;
		// free(data->token);
		// data->token = NULL;
		// free(data->tree);
		// data->tree = NULL;
		
		data = temp_data;
	}
}

/* void	clean(t_data *data, int ex)
{
	if (!data)
		exit(1);
	free_env(data->envp);
	free_token(data->token);
	rl_clear_history();
	exit(ex);
} */

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

