/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:46:27 by bde-souz          #+#    #+#             */
/*   Updated: 2024/07/23 16:33:13 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	signal_main(int signal_num)
{
	//ft_putstr_fd("Entrou no signal main\n", 2);
	if(signal_num == SIGINT)
	{
		rl_replace_line("", 0);
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		G_EXIT_CODE = 130;
		//print_error(NULL, 130);
	}
}


void	signal_heredoc_checker(int status)
{
	//ft_putstr_fd("test\n", 2);
	//printf("status: %d", status);
	if (WTERMSIG(status) == 3)// Se o sinal for terminado com status 3 (ctrl + barra)
	{
			//ft_putstr_fd("ctrl + barra\n", 2);
			ft_putstr_fd("Quit (core dumped)\n", 2);
			G_EXIT_CODE = 131;
			return ;
	}
	else if (WTERMSIG(status) == 2) // se o sinal for terminado com status 2 (ctrl + c)
	{
			//ft_putstr_fd("ctrl + c\n", 2);
			ioctl(0, TIOCSTI, "\n");
			// rl_replace_line("", 0);
			// //ft_putstr_fd("\n", 2);
			// ft_putstr_fd("\n", STDERR_FILENO);
			// rl_on_new_line();
			// rl_redisplay();
			// G_EXIT_CODE = 130;
			// return ;
	}
}

void	signal_here_doc(int signal_num)
{
	//ft_putstr_fd("Estrou no signal HERE_DOC\n", 2);
	if (signal_num == SIGINT)
	{
		write(1, "\n", 1);
		rl_redisplay();
		ioctl(0, TIOCSTI, "\n");
	}
}

void	signal_child(int signal_num)
{
	(void)signal_num;
	ft_putstr_fd("Entrou no signal child\n", 2);
	// write(2, "a\n", 2);
	// if (signal_num == SIGINT)
	// 	write(STDERR_FILENO, "\n", 1);
	// if (signal_num == SIGQUIT)
	// 	write(STDERR_FILENO, "Quit (core dumped)\n", 19);

}

void	ft_catch_signal(int id)
{
	//1 = MAIN, 2 = CHILD, 3 = HERE_DOC, 4 = PIPE
	
	if (id == MAIN)
	{
		//ft_putstr_fd("catch_signal main\n", 2);
		signal(SIGINT, signal_main); //ctrl + c
		signal(SIGTERM, SIG_IGN); //ctrl + D
		signal(SIGQUIT, SIG_IGN); //ctrl + barra
	}
	else if (id == CHILD)
	{
		//ft_putstr_fd("catch_signal child\n", 2);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (id == HERE_DOC)
	{
		//ft_putstr_fd("catch_signal here_doc\n", 2);
		signal(SIGINT, SIG_DFL);
		signal(SIGTERM, SIG_IGN); //ctrl + D
	}
	else if (id == PIPE)
	{
		ft_putstr_fd("PIPE\n", 2);
	
	}
	
}

void	ft_signal_ignore(void)
{
	//ft_putstr_fd("Sinal ignorado\n", 2);
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}