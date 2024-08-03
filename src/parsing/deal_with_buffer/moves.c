/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:28:05 by bde-souz          #+#    #+#             */
/*   Updated: 2024/07/19 19:28:00 by nsouza-o         ###   ########.fr       */
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

int	move_without_quotes(char *buffer, int i, t_data *data)
{
	int start;

	start = i;
	while(buffer[i] && (!(buffer[i] >= 7 && buffer[i] <= 32) || check_for_open_quotes(buffer, i)))
		i++;
	save_substring(buffer, start, (i - 1), data);
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
