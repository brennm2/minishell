/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:46:27 by bde-souz          #+#    #+#             */
/*   Updated: 2024/08/09 19:42:50 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	signal_main(int signal_num)
{
	if (signal_num == SIGINT)
	{
		rl_replace_line("", 0);
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		g_exit_code = 130;
	}
}

void	signal_child(int signal_num)
{
	if (signal_num == SIGINT)
		write(1, "\n", 1);
	if (signal_num == SIGQUIT)
		write(1, "Quit (core dumped)\n", 19);
}

void	signal_here_doc(int signal_num)
{
	ft_putstr_fd("Estrou no signal HERE_DOC\n", 2);
	if (signal_num == SIGINT)
	{
		write(1, "\n", 1);
		rl_redisplay();
		ioctl(0, TIOCSTI, "\n");
	}
}

void	ft_signal_def(void)
{
	signal(SIGTERM, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}
