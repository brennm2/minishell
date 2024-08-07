/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:33:40 by bde-souz          #+#    #+#             */
/*   Updated: 2024/08/07 11:44:36 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	print_error(char *error_type, int error_code, t_data *data)
{
	if (error_type != NULL)
	{
		write(2, "minishell: ", 12);
		write(2, error_type, ft_strlen(error_type));
		write(2, "\n", 1);
	}
	data->exit_code = error_code;
}

void	p_error_flag(char *error_type, int error_code, t_data *data,
	int exit_flag)
{
	if (error_type != NULL)
	{
		write(2, "minishell: ", 12);
		write(2, error_type, ft_strlen(error_type));
		write(2, "\n", 1);
	}
	ft_exit_flag(error_code, exit_flag, data);
}
