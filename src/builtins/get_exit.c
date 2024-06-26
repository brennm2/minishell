/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:19:54 by bde-souz          #+#    #+#             */
/*   Updated: 2024/06/26 17:04:12 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	exit_numeric_error(t_token *token, int option)
{
	if (option == 0)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(token->next->str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	else
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(token->str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	exit (2);
}

void	too_many_argument_error(t_token	*token)
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
	exit_numeric_error(token, 1);
}

void	exit_negative(t_token *token)
{
	int	number;

	number = ft_atoi(token->str);
	number = 256 - (number * -1);
	printf("exit code: %d\n", number);
	exit(number);
}

void	only_exit(t_data *data)
{
	ft_putstr_fd("exit\n", 1);
	free_env(data->envp);
	free_token(data->token);
	//ft_free_data(data, 2);
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
			return (too_many_argument_error(data->token->next));
		if (data->token->next->str[0] == '-') // Se tiver numeros negativos "exit -1"
			i++;
		while (ft_isdigit(data->token->next->str[i]) == 1) // Se <TOKEN->STR> / "exit 123" for somente numeros
		{
			i++;
			if (data->token->next->str[i] == '\0') // Se <TOKEN->STR[i]> acabar e for tudo numero
			{
				if (ft_atoi(data->token->next->str) < 0)
					return (exit_negative(data->token->next));
				ft_putstr_fd("exit\n", 1);
				exit(ft_atoi(data->token->next->str));
			}
		}
		exit_numeric_error(data->token, 0);//Se saiu do loop entao encotrou algo que nao e numerico
	}
}
