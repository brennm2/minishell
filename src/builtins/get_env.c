/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:13:12 by bde-souz          #+#    #+#             */
/*   Updated: 2024/06/19 15:43:10 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	env_error_invalid(t_data *data)
{
	write(2, "env: invalid option -- ", 23);
	write(2, "'", 1);
	write(2, &data->token->next->str[1], 1); //Escreve um caracter da flag
	write(2, "'", 1);
	write(2, "\n", 1);
	print_error(NULL, 125); //Escreva o erro
}

void	env_error_option(t_data *data)
{
	write(2, "env: ", 5);
	write(2, "'", 1);
	write(2, data->token->next->str, ft_strlen(data->token->next->str));
	write(2, "': No such file or directory", 29);
	write(2, "\n", 1);
	print_error(NULL, 127);
}

void	display_env(t_envp *envp)
{
	while (envp)
	{
		write(1, envp->key, ft_strlen(envp->key));
		write(1, "=", 1);
		write(1, envp->value, ft_strlen(envp->value));
		write(1, "\n", 1);
		envp = envp->next;
	}
	return (set_exit_code(0));
}

void	get_builtin_env(t_data *data)
{
	t_envp	*temp_env;

	//data->token->next->type = flag;
	temp_env = data->envp;
	if (data->token->next) // Se for "env ..."
	{
		if (data->token->next->str[0] == '-' && data->token->next->str[1]) //Se for Option "-n"
		{
			env_error_invalid(data);
			return ;
		}
	}
	if (data->token->next) // Se for "env ..."
	{
		if (data->token->next->str[0] == '-') // Se for somente "-", retornar sem fazer nada
			return ;
		env_error_option(data);
		return ;
	}
	else //Se nenhuma dessas condicoes foi atendida...
		display_env(temp_env); // Mostra a lista de env
}
