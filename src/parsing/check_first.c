/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_first.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:28:38 by bde-souz          #+#    #+#             */
/*   Updated: 2024/05/27 16:32:48 by bde-souz         ###   ########.fr       */
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
					printf("ERROR_PIPE_DOUBLE\n");//print ERROR Double Pipes
				else
					printf("ERROR_PIPE_SINGLE\n");//print ERROR Single Pipe
			}
			else if (ft_strchr("|<>", buffer[ft_strlen(buffer) - 1]))
			{
				if (buffer[ft_strlen(buffer) - 1] == '|')
					printf("ERROR_PIPE_FINAL\n");
				else
					printf("ERROR_REDIR\n");
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

	if (!buffer)
	{
		printf("Buffer nao existe\n");
		//free
		//print error
		//exit 0
	}
	if(is_all_space(buffer) || check_for_quotes(buffer) 
		|| !check_for_syntax_error(buffer))
		return (false);
	return (true);
}