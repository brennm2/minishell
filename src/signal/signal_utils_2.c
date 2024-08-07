/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:02:13 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/08/07 11:11:00 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	sig_quit(int sig)
{
	(void)sig;
}
void	sig_int(int sig)
{
	(void)sig;
}

void test_sigint(int signal)
{
	if (signal == SIGINT)
		write(STDERR_FILENO, "\n", 1);
	if (signal == SIGQUIT)
		write(STDERR_FILENO, "Quit (core dumped)\n", 20);
}