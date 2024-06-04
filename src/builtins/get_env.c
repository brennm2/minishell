/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:13:12 by bde-souz          #+#    #+#             */
/*   Updated: 2024/06/04 11:44:02 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	env_error_invalid(t_data *data)
{
	// env -a
	//env: invalid option -- 'a'
	write(2, "env: invalid option -- ", 23);
	write(2, "'", 1);
	write(2, &data->token->next->str[1], 1); //Escreve um caracter da flag
	write(2, "'", 1);
	write(2, "\n", 1);
	print_error(NULL, 125); //Escreva o erro
}

void	get_builtin_env(t_data *data)
{
	t_envp	*temp_env;
	data->token->next->type = flag;
	temp_env = data->envp;
	
	if(data->token->next->str[0] == '-')
	{
		if(data->token->next->str[0] == '-' && data->token->next->str[1])
		{
			env_error_invalid(data);
			return ;
		}
		return ;
	}
	else if (data->token->next->str)
	{
		//env 343434
		//env: ‘34341414’: No such file or directory
			
		write(2, "env: ", 5);
		write(2, "'", 1);
		write(2, data->token->next->str, ft_strlen(data->token->next->str));
		write(2, "': No such file or directory", 29);
		write(2, "\n", 1);
		print_error(NULL, 127);
	}
	else
	{
		while(temp_env)
		{
			write(1, temp_env->key, ft_strlen(temp_env->key));
			write(1, "=", 1);
			write(1, temp_env->value, ft_strlen(temp_env->value));
			write(1, "\n", 1);
			temp_env = temp_env->next;
		}
	}
}
