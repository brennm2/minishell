/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:46:27 by bde-souz          #+#    #+#             */
/*   Updated: 2024/07/05 12:04:13 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	signal_main(int signal_num)
{
	if(signal_num == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putstr_fd("\n", STDERR_FILENO);
		rl_on_new_line();
		rl_redisplay();
		print_error(NULL, 130);
	}
}


void	ft_catch_signal(int id)
{
	//1 = MAIN, 2 = CHILD, 3 = HERE_DOC, 4 = PIPE, 5 = IGNORE
	
	if (id == MAIN)
	{
		signal(SIGINT, signal_main);
		signal(SIGTERM, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	
}
