/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exit_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:56:34 by bde-souz          #+#    #+#             */
/*   Updated: 2024/08/09 13:23:08 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	exit_number(t_data *data, t_token *token, int exit_flag, int number)
{
	int	temp_exit;

	(void) token;
	temp_exit = 0;
	if (exit_flag == 0)
	{
		temp_exit = number;
		ft_putstr_fd("exit\n", 1);
		free_env(data->envp);
		free_token(data->token);
		free_tree(data->tree);
		free_data(data);
		exit(temp_exit);
	}
	else
	{
		temp_exit = number;
		free_env(data->envp);
		free_token(data->token);
		free_tree(data->tree);
		free_data(data);
		exit(temp_exit);
	}
}

void	free_to_exit(t_data *data)
{
	free_env(data->envp);
	free_token(data->token);
	free_tree(data->tree);
	free_data(data);
}

long long	ft_atoll(const char *str)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (ft_isdigit((unsigned char)*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (sign * result);
}
