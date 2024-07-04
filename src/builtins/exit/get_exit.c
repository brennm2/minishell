/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:19:54 by bde-souz          #+#    #+#             */
/*   Updated: 2024/07/04 12:10:19 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	exit_numeric_error(t_data *data, int option)
{
	if (option == 0)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(data->token->next->str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	else
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(data->token->str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	free_env(data->envp);
	free_token(data->token);
	free_data(data);
	exit (2);
}

void	too_many_argument_error(t_token	*token, t_data *data)
{
	int	i;

	i = 0;
	while (ft_isdigit(token->str[i]) == 1)
	{
		i++;
		if (token->str[i] == '\0')
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			print_error(NULL, 1);
			return ;
		}
	}
	exit_numeric_error(data, 1);
}

void	exit_negative(t_token *token, t_data *data)
{
	int	number;

	number = ft_atoi(token->str);
	number = 256 - (number * -1);
	free_env(data->envp);
	free_token(data->token);
	free_data(data);
	exit(number);
}

void	only_exit(t_data *data)
{
	ft_putstr_fd("exit\n", 1);
	free_env(data->envp);
	free_token(data->token);
	free_data(data);
	exit (G_EXIT_CODE);
}

void	get_exit(t_data *data)
{
	int	i;

	i = 0;
	if (!data->token->next) //Se for somente "exit"
		only_exit(data);
	else if (data->token->next->str) // Se existir <TOKEN->NEXT> / "exit algumacoisa"
	{
		if (data->token->next->next) // Se for "exit ... ..."
			return (too_many_argument_error(data->token->next, data));
		if (data->token->next->str[0] == '-') // Se tiver numeros negativos "exit -1"
			i++;
		while (ft_isdigit(data->token->next->str[i]) == 1) // Se <TOKEN->STR> / "exit 123" for somente numeros
		{
			i++;
			if (data->token->next->str[i] == '\0') // Se <TOKEN->STR[i]> acabar e for tudo numero
			{
				if (ft_atoi(data->token->next->str) < 0)
					return (exit_negative(data->token->next, data));
				ft_putstr_fd("exit\n", 1);
				exit(ft_atoi(data->token->next->str));
			}
		}
		exit_numeric_error(data, 0);//Se saiu do loop entao encotrou algo que nao e numerico
	}
}
