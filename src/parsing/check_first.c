/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_first.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:28:38 by bde-souz          #+#    #+#             */
/*   Updated: 2024/05/28 15:20:35 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

bool	is_all_space(char *buffer)
{
	int i;

	//test
	i = 0;
	while(buffer[i++])
		if (buffer[i] != ' ')
			return (false);
	return (true);
}

bool	check_for_quotes(char *buffer) // Procura por D_QUOTES ou S_QUOTES nao fechadas
{
	int s_quotes;
	int d_quotes;
	int i;
	
	i = 0;
	s_quotes = 0;
	d_quotes = 0;
	while(buffer[i++])
	{
		if (buffer[i] == S_QUOTES && !d_quotes)
			s_quotes = !s_quotes;
		else if (buffer[i] == D_QUOTES && !s_quotes)
			d_quotes = !d_quotes;
	}
	if (d_quotes != 0 || s_quotes != 0)
	{
		//print error
		return (true);
	}
	else
		return (false);
}

bool	check_for_syntax_error(char *buffer)
{
	if (!buffer || ft_strchr("|<>", buffer[0])
		|| ft_strchr("|<>", buffer[ft_strlen(buffer) - 1]))
	{
		if (buffer)
		{
			if (buffer[0] == '|')
			{
				if (buffer[1] == '|')
					print_error(ERROR_PIPE_DOUBLE, 2);
				else
					print_error(ERROR_PIPE_SINGLE, 2);
			}
			else if (ft_strchr("|<>", buffer[ft_strlen(buffer) - 1]))
			{
				if (buffer[ft_strlen(buffer) - 1] == '|')
					print_error(ERROR_PIPE_FINAL, 1);
				else
					print_error(ERROR_REDIR, 2);
			}
		}
		//free buffer?
		return (false);
	}
	//free buffer?
	return (true);
}


bool	valid_input(char *buffer)
{

	if (!buffer || buffer == NULL)
	{
		printf("Buffer nao existe\n"); //#TODO <-- Retirar
		//free
		//print error
		exit (G_EXIT_CODE);
	}
	if(is_all_space(buffer) || check_for_quotes(buffer) 
		|| !check_for_syntax_error(buffer))
		return (false);
	return (true);
}