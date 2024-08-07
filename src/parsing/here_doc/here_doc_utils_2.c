/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:28:07 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/08/07 14:32:59 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

char	*erase_the_quote_hd(char *delimiter, int i)
{
	char	*unquote_str;
	char	*temp;

	temp = ft_calloc(sizeof(char), i + 1);
	ft_strlcpy(temp, delimiter, i + 1);
	i++;
	unquote_str = ft_strjoin(temp, delimiter + i);
	free(temp);
	return (unquote_str);
}

char	*expand_hd(t_data *data, char *buffer, bool flag)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	if (flag)
		return (buffer);
	while (buffer[++i])
	{
		if (buffer[i] == '$' && buffer[i + 1] && buffer[i + 1])
		{
			buffer = is_expand_util_hd(buffer, data, i, j);
			if (!buffer)
				break ;
			i = -1;
			continue ;
		}
	}
	return (buffer);
}
