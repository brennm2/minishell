/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct_space.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:03:06 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/07/19 19:19:28 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*join;

	if (!s1)
		s1 = ft_strdup("");
	i = ft_strlen(s1);
	j = -1;
	join = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (join == NULL)
	{
		free(s1);
		return (NULL);
	}
	while (s1[++j])
		join[j] = s1[j];
	j = -1;
	while (s2[++j])
		join[i + j] = s2[j];
	join[i + j] = '\0';
	free(s1);
	return (join);
}

char	*copy_char(char *buffer, int i)
{
	if (!ft_strncmp(buffer + i, "|", 1))
		return (ft_strdup("|"));
	if (!ft_strncmp(buffer + i, ">", 1) && ft_strncmp(buffer + i + 1, ">", 1))
		return (ft_strdup(">"));
	if (!ft_strncmp(buffer + i, "<", 1) && ft_strncmp(buffer + i + 1, "<", 1))
		return (ft_strdup("<"));
	if (!ft_strncmp(buffer + i, ">>", 1))
		return (ft_strdup(">>"));
	if (!ft_strncmp(buffer + i, "<<", 1))
		return (ft_strdup("<<"));
	return (NULL);
}

char	*put_space_on(char *buffer, int i)
{
	char	*new_buffer;
	char	*space;
	char	*symbol;

	space = ft_strdup(" ");
	symbol = copy_char(buffer, i);
	new_buffer = ft_calloc(sizeof(char), i + 1);
	if (!new_buffer)
	{
		free(space);
        free(symbol);
		return (NULL);
	}
	ft_strlcpy(new_buffer, buffer, i + 1);
	new_buffer = ft_strjoin_free(new_buffer, space);
	new_buffer = ft_strjoin_free(new_buffer, symbol);
	new_buffer = ft_strjoin_free(new_buffer, space);
	if (!ft_strncmp(buffer + i, ">>", 2))
		i++;
	if (!ft_strncmp(buffer + i, "<<", 2))
		i++;
	new_buffer = ft_strjoin_free(new_buffer, buffer + i + 1);
	free(space);
	free(symbol);
	return (free(buffer), new_buffer);
}

char	*check_spaces(char *buffer)
{
	int	i;
	
	i = -1;
	while (buffer[++i])
	{
		if ((buffer[i] == '|' || buffer[i] == '>' || buffer[i] == '<' || \
			(buffer[i] == '>' && buffer[i + 1] == '>')) && quote_status(buffer, i) == 0)
		{
			buffer = put_space_on(buffer, i);
			i += 2;
		}
		if (!ft_strncmp(buffer + i, ">", 1) && \
		ft_strncmp(buffer + i - 1, ">", 1))
			i++;
	}
	return (buffer);
}
