/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:57:11 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/08/07 19:33:05 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	signal_heredoc(int signal, t_data *data, char *delimiter, char *here)
{
	static t_data	*data_temp;
	static char		*delimiter_temp;
	static char		*here_temp;

	if (signal == -1)
	{
		data_temp = data;
		delimiter_temp = delimiter;
		here_temp = here;
	}
	else if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_redisplay();
		free(delimiter_temp);
		free(here_temp);
		clean_hd(data_temp, 130);
	}
}

void	ft_catch_signal(int id)
{
	if (id == MAIN)
	{
		signal(SIGINT, (void *)signal_main);
		signal(SIGTERM, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (id == CHILD)
	{
		signal(SIGINT, signal_child);
		signal(SIGQUIT, signal_child);
	}
	else if (id == HERE_DOC)
	{
		signal(SIGINT, (void *)signal_heredoc);
		signal(SIGTERM, (void *)signal_heredoc);
	}
	else if (id == PIPE)
		ft_putstr_fd("PIPE\n", 2);
}

void	reset_fd_signals(int fd1, int fd2)
{
	ft_catch_signal(MAIN);
	dup2(fd1, STDIN_FILENO);
	dup2(fd2, STDOUT_FILENO);
}

void	ft_signal_ignore(void)
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}
