/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:19:54 by bde-souz          #+#    #+#             */
/*   Updated: 2024/08/06 13:15:31 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	exit_numeric_error(t_data *data, t_token *token, int option,
	int exit_flag)
{
	if (option == 0)
	{
		if (exit_flag == 0)
			ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(token->next->str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	else
	{
		if (exit_flag == 0)
			ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(token->next->str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	free_env(data->envp);
	free_token(data->token);
	free_tree(data->tree);
	free_data(data);
	exit (2);
}

void	too_many_error(t_token	*token, t_data *data, int exit_flag)
{
	int	i;

	i = 0;
	while (ft_isdigit(token->str[i]) == 1)
	{
		i++;
		if (token->str[i] == '\0')
		{
			if (exit_flag == 0)
				write (2, "exit\n", 6);//ft_putstr_fd("exit\n", 2);
			write(2, "minishell: exit: too many arguments\n", 37);
			if (data->exit_code != 0)
				ft_exit_flag(data->exit_code, exit_flag, data);
			else
				ft_exit_flag(1, exit_flag, data);
			return ;
		}
	}
	exit_numeric_error(data,token, 1, exit_flag);
}

void	exit_negative(t_token *token, t_data *data, int exit_flag)
{
	int	number;

	number = ft_atoi(token->str);
	number = 256 - (number * -1);
	(void)exit_flag;
	free_env(data->envp);
	free_token(data->token);
	free_tree(data->tree);
	free_data(data);
	exit(number);
}

void	only_exit(t_data *data, t_token *token, int exit_flag)
{
	int	temp_exit;

	temp_exit = 0;
	if (exit_flag == 0) // se for no pai
	{
		if (token->next)
			temp_exit = ft_atoi(token->next->str);
		else
			temp_exit = data->exit_code;
		ft_putstr_fd("exit\n", 2);
		free_env(data->envp);
		free_token(data->token);
		free_tree(data->tree);
		free_data(data);
		exit(temp_exit);
	}
	else
	{
		temp_exit = data->exit_code;
		free_env(data->envp);
		free_token(data->token);
		free_tree(data->tree);
		free_data(data);
		exit(temp_exit);
	}
}

void	get_exit(t_data *data, t_token *token, int exit_flag)
{
	int	i;

	i = 0;
	if (!token->next || token->next->type != string) //Se for somente "exit"
		only_exit(data, token, exit_flag);
	else if (token->next->str) // Se existir <TOKEN->NEXT> / "exit algumacoisa"
	{
		if (token->next->next && token->next->next->type == string) // Se for "exit ... ..."
			return (too_many_error(token->next, data, exit_flag));
		if (token->next->str[0] == '-' || token->next->str[0] == '+') // Se tiver numeros negativos "exit -1"
			i++;
		while (ft_isdigit(token->next->str[i]) == 1) // Se <TOKEN->STR> / "exit 123" for somente numeros
		{
			i++;
			if (token->next->str[i] == '\0') // Se <TOKEN->STR[i]> acabar e for tudo numero
			{
				if (ft_atoi(token->next->str) < 0)
					return (exit_negative(token->next, data, exit_flag));
				exit_number(data, token, exit_flag, ft_atoi(token->next->str)); //only_exit(data, token, exit_flag);
			}
		}
		exit_numeric_error(data, token, 0, exit_flag);//Se saiu do loop entao encotrou algo que nao e numerico
	}
}
