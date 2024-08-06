/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exit_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:56:34 by bde-souz          #+#    #+#             */
/*   Updated: 2024/08/06 13:16:06 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	exit_number(t_data *data, t_token *token, int exit_flag, int number)
{
	int	temp_exit;

	(void) token;
	temp_exit = 0;
	if (exit_flag == 0) // se for no pai
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
