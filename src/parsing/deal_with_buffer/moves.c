/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:28:05 by bde-souz          #+#    #+#             */
/*   Updated: 2024/08/02 17:41:13 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

int	move_space(char *buffer, int i)
{
	while(buffer[i] && (buffer[i] >= 7 && buffer[i] <= 32))
		i++;
	return(i);
}

bool	check_for_open_quotes(char *buffer, int i)
{
	bool	dquotes;
	bool 	squotes;

	dquotes = false;
	squotes = false;

	while(i >= 0 && buffer[i])
	{
		if(buffer[i] == S_QUOTES && dquotes == false)
			squotes = !squotes;
		if(buffer[i] == D_QUOTES && squotes == false)
			dquotes = !dquotes;
		i--;
	}
	if (squotes == true || dquotes == true)
		return (true);
	else
		return (false);
}

int get_size(char *buffer, int i)
{
	int		size;
	char	c;

	c = buffer[i];
	size = 1;
	if (buffer[i] == S_QUOTES || buffer[i] == D_QUOTES)
	{
		while (buffer[++i] != c)
			size++;
		return (size + 1);		
	}
	else
	{
		while(buffer[++i] && (!(buffer[i] >= 7 && buffer[i] <= 32)))
		size++;
		return (size);
	}
}

int	move_without_quotes(char *buffer, int i, t_data *data)
{
	int size;

	/* start = i;
	while(buffer[i] && (!(buffer[i] >= 7 && buffer[i] <= 32) || check_for_open_quotes(buffer, i)))
		i++; */
	size = get_size(buffer, i);
	i = save_substring(buffer, size, i, data);
	return(i);
}

int	check_for_string(char *buffer, int start)
{
	while(buffer[start])
	{
		if (buffer[start] && (buffer[start] >= 7 && buffer[start] <= 32))
			start++;
		else
			return (start);
	}
	return (start);
}
