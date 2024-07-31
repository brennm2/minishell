/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:48:41 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/07/31 18:34:18 by bde-souz         ###   ########.fr       */
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
	{
		if (WTERMSIG(status) == SIGINT)
		{
			write(1, "\n", 1);
			set_exit_code(WTERMSIG(status) + 128, data);
		}
		if (WCOREDUMP(status))
		{
			write(1, "Quit (core dumped)\n", 20);
			set_exit_code(WTERMSIG(status) + 128, data);
		}
		//set_exit_code(WTERMSIG(status), data);
	}
}

