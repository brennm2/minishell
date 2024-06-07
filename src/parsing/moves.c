/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:28:05 by bde-souz          #+#    #+#             */
/*   Updated: 2024/06/07 16:57:04 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"


int	move_space(char *buffer, int i)
{
	while(buffer[i] && (buffer[i] >= 7 && buffer[i] <= 32))
		i++;
	return(i);
}

int	move_without_quotes(char *buffer, int i, t_data *data)
{
	int start;

	start = i;
	while(buffer[i] && !(buffer[i] >= 7 && buffer[i] <= 32
		|| buffer[i] == D_QUOTES || buffer[i] == S_QUOTES))
		i++;
	save_substring(buffer, start, (i - 1), data);
	return(i);
}

int	move_with_quotes(char *buffer, int i, int flag, t_data *data)
{
	int start;

	start = i;
	i++;
	while(buffer[i] && buffer[i] != flag)
		i++;
	if(!buffer[i])
	{
		printf("SINTAX ERROR! \n"); //#TODO CRIAR FUNC DE ERROR / Porque?
		return (i);
	}
	if (buffer[i] == flag)
		i++;
	save_substring(buffer, (start + 1), (i - 2), data);
	if (flag == S_QUOTES)
		data->token->type = not_expander;
	return(i);
}