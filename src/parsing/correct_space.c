/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct_space.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:03:06 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/06/26 16:36:59 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*join;

	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	i = ft_strlen(s1);
	j = 0;
	join = (char *)malloc(sizeof(s1[0]) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (join == NULL)
		return (NULL);
	while (s1[j])
	{
		join[j] = s1[j];
		j++;
	}
	j = -1;
	while (s2[++j])
		join[i + j] = s2[j];
	free(s1);
	join[i + j] = '\0';
	return (join);
}

char	*copy_char(char *buffer, int i)
{
	if (!ft_strncmp(buffer + i, "|", 1))
		return ("|");
	if (!ft_strncmp(buffer + i, ">", 1) && ft_strncmp(buffer + i + 1, ">", 1))
		return (">");
	if (!ft_strncmp(buffer + i, "<", 1) && ft_strncmp(buffer + i + 1, "<", 1))
		return ("<");
	if (!ft_strncmp(buffer + i, ">>", 1))
		return (">>");
	if (!ft_strncmp(buffer + i, "<<", 1))
		return ("<<");
	return (NULL);
}

char	*put_space_on(char *buffer, int i)
{
	char	*new_buffer;
	//char	*temp; //#TODO Func nao utilizada. Comentada por causa das flags

	new_buffer = ft_calloc(sizeof(char), i + 1);
	if (!new_buffer)
		return (NULL);
	ft_strlcpy(new_buffer, buffer, i + 1);
	new_buffer = ft_strjoin_free(new_buffer, " ");
	new_buffer = ft_strjoin_free(new_buffer, copy_char(buffer, i));
	new_buffer = ft_strjoin_free(new_buffer, " ");
	if (!ft_strncmp(buffer + i, ">>", 2))
		i++;
	if (!ft_strncmp(buffer + i, "<<", 2))
		i++;
	new_buffer = ft_strjoin_free(new_buffer, buffer + i + 1);
	free(buffer);
	return (new_buffer);
}

char	*check_spaces(char *buffer)
{
	int	i;
	int	quote_flag;

	quote_flag = 1;
	i = -1;
	while (buffer[++i])
	{
		if (buffer[i] == D_QUOTES || buffer[i] == S_QUOTES)
			quote_flag *= -1;
		if ((buffer[i] == '|' || buffer[i] == '>' || buffer[i] == '<' || \
			(buffer[i] == '>' && buffer[i + 1] == '>')) && quote_flag > 0)
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
