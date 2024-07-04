/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:12:37 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/07/04 16:38:42 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	open_here_doc(char *delimiter)
{
	char *buffer;

	while (1)
	{
		buffer = readline("> ");
		if (!ft_strcmp(delimiter, buffer))
			return ;
		printf("%s\n", buffer);
	}	
}

bool	is_here_doc(t_data *data)
{
	char	*delimiter;
	t_data	*data_aux;

	data_aux = data;
	while (data_aux->token->str)
	{
   		if (!ft_strcmp(data_aux->token->str, "<<"))
		{
			delimiter = ft_strdup(data_aux->token->next->str);
			open_here_doc(delimiter);
			return (true);
		}
		data_aux->token = data_aux->token->next;
	}
	return (false);
}