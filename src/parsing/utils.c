/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:41:04 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/06/21 19:16:27 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_is_especial(int c)
{
	if ((c >= 33 && c <= 47))
		return (1);
	return (0);
}

char	*ft_strjoin_ex(char *s1, char const *s2)
{
	int		strlen;
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	strlen = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (strlen + 1));
	if (!str)
		return (NULL);
	while (s1 && s2)
	{
		while (s1[i])
			str[j++] = s1[i++];
		i = 0;
		while (s2[i])
			str[j++] = s2[i++];
		str[j] = '\0';
		free(s1);
		return (str);
	}
	return (NULL);
}

int	quote_status(char *str, int i)
{
	int	j;
	int	s_flag;
	int	d_flag;

	s_flag = 1;
	d_flag = 2;
	j = -1;
	while (str[++j] && j <= i)
	{
		if (str[j] == S_QUOTES && d_flag > 0)
			s_flag *= -1;
		if (str[j] == D_QUOTES && s_flag > 0)
			d_flag *= -1;
	}
	if (s_flag < 0)
		return (s_flag);
	if (d_flag < 0)
		return (d_flag);
	return (0);
}
