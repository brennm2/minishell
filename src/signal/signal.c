/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:46:27 by bde-souz          #+#    #+#             */
/*   Updated: 2024/07/24 15:48:57 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	signal_main(int signal_num)
{
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

void	signal_child(int signal_num)
{
	//ft_putstr_fd("Estrou no signal child\n", 2);
	if (signal_num == SIGINT)
		write(1, "\n", 1);
	if (signal_num == SIGQUIT)
		write(1, "Quit (core dumped)\n", 19);

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
	ft_putstr_fd("Estrou no signal HERE_DOC\n", 2);
	if (signal_num == SIGINT)
	{
		write(1, "\n", 1);
		rl_redisplay();
		ioctl(0, TIOCSTI, "\n");
	}
}
