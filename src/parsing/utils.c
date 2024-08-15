/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:41:04 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/08/15 18:29:20 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_is_especial(int c)
{
	if ((c >= 33 && c <= 47) || (c >= 58 && c <= 64) || (c >= 91 && c <= 94) \
		|| (c == 96) || (c >= 123 && c <= 127))
		return (1);
	return (0);
}

int	ft_is_especial_2(int c)
{
	if (c == 35 || (c >= 37 && c <= 38) || (c >= 40 && c <= 41) || \
		(c >= 43 && c <= 47) || (c >= 58 && c <= 62) || (c >= 91 && c <= 94) \
		|| c == 96 || (c >= 123 && c <= 126))
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

void	remove_quotes_ex(t_token *token, int j)
{
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (token->str[i] && i < j)
	{
		if ((token->str[i] == S_QUOTES || token->str[i] == D_QUOTES) && i != j)
		{
			k = i;
			i++;
			while (token->str[i] && (token->str[i] != token->str[k] || i == j))
				i++;
			erase_the_quote(token, k);
			erase_the_quote(token, i - 1);
			if (i < j)
				j = j - 2;
			i = i - 1;
			
		}
		else
			i++;
	}
	token->quote_flag = true;
}
