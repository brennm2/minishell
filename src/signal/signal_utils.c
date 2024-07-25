/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:57:11 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/07/25 15:04:59 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	signal_heredoc(int signal_num)
{
	//ft_putstr_fd("entrou aqui\n", 1);
	if (signal_num == SIGINT)
	{
		//ft_putstr_fd("aasdasda", 1);
		//ioctl(0, TIOCSTI, "\n");
		exit (69);
		
		// write(1, "\n", 1);
		// rl_redisplay();
	}
}

void	ft_catch_signal(int id)
{
	if (id == MAIN)
	{
		//ft_putstr_fd("Entrou aqui main\n", 2);
		signal(SIGINT, signal_main); //ctrl + c
		signal(SIGTERM, SIG_IGN); //ctrl + D
		signal(SIGQUIT, SIG_IGN); //ctrl + barra
	}
	else if (id == CHILD)
	{
		signal(SIGINT, signal_child);
		signal(SIGQUIT, signal_child);
	}
	else if (id == HERE_DOC)
	{
		//ft_putstr_fd("HERE_DOC\n", 2);
		signal(SIGINT, signal_heredoc);
		signal(SIGTERM, SIG_DFL); //ctrl + D
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
	//ft_putstr_fd("Sinal ignorado\n", 2);
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}
