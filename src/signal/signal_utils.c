/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:57:11 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/07/23 16:23:27 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

// void	ft_catch_signal(int id)
// {
// 	if (id == MAIN)
// 	{
// 		//ft_putstr_fd("Entrou aqui main\n", 2);
// 		signal(SIGINT, signal_main); //ctrl + c
// 		signal(SIGTERM, SIG_IGN); //ctrl + D
// 		signal(SIGQUIT, SIG_IGN); //ctrl + barra
// 	}
// 	else if (id == CHILD)
// 	{
// 		signal(SIGINT, signal_child);
// 		signal(SIGQUIT, signal_child);
// 	}
// 	else if (id == HERE_DOC)
// 	{
// 		ft_putstr_fd("HERE_DOC\n", 2);
// 		signal(SIGINT, SIG_DFL);
// 		signal(SIGTERM, SIG_IGN); //ctrl + D
// 	}
// 	else if (id == PIPE)
// 		ft_putstr_fd("PIPE\n", 2);
	
// }

void	reset_fd_signals(int fd1, int fd2)
{
	ft_catch_signal(MAIN);
	dup2(fd1, STDIN_FILENO);
	dup2(fd2, STDOUT_FILENO);
}

// void	ft_signal_ignore(void)
// {
// 	//ft_putstr_fd("Sinal ignorado\n", 2);
// 	signal(SIGTERM, SIG_IGN);
// 	signal(SIGQUIT, SIG_IGN);
// 	signal(SIGINT, SIG_IGN);
// }
