/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exit_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:56:34 by bde-souz          #+#    #+#             */
/*   Updated: 2024/08/09 11:49:10 by nsouza-o         ###   ########.fr       */
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
