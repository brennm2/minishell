/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:57:11 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/07/30 10:46:27 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	signal_heredoc(int signal, t_data *data, char *delimiter, char *here)
{
	//ft_putstr_fd("entrou aqui\n", 1);
	static t_data *data_temp;
	static char	*delimiter_temp;
	static	char *here_temp;
	
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
		// free_env(data_temp->envp);
		// free_token(data_temp->token);
		// free_data(data_temp);
		//exit(130);
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
		signal(SIGINT, (void *)signal_heredoc);
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
