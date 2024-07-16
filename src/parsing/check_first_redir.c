/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_first_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:03:16 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/07/16 17:06:33 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

bool	check_for_redir(char *buffer, t_data *data)
{
	int	i;
	char	c;

	i = -1;
	while (buffer[++i])
	{
		if (buffer[i] == '<' && !quote_status(buffer, i))
			check_for_redout(buffer, i, data);
		if (buffer[i] == '>' && !quote_status(buffer, i))
			check_for_redin(buffer, i, data);
	}
	return (false);
	
}
			/* c = buffer[i];
			while(buffer[i] && (buffer[i] == ' '))
				i++;
			if (!buffer[i] && c == '<')
			{
				print_error(ERROR_REDIR, 2, data);
				return (true);
			}
			if (buffer[i] == '<' || buffer[i] == '>')
			{
				ft_putstr_fd("syntax error near unexpected token `", 2);
				ft_putchar_fd(buffer[i], 2);
				ft_putstr_fd("\'\n", 2);
				data->exit_code = 2;
				return (true);
			} */