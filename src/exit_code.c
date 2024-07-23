/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:48:41 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/07/19 14:50:16 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	set_exit_code(int code, t_data *data)
{
	data->exit_code = code;
}

void	update_exit_code(int status, t_data *data)
{
	if (WIFEXITED(status))
		set_exit_code(WEXITSTATUS(status), data);
	else if (WIFSIGNALED(status))
		set_exit_code(WTERMSIG(status), data);
}

