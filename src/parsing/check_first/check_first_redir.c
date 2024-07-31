/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_first_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:03:16 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/07/31 14:19:30 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

bool	check_valid_redir(char *buffer, int i)
{
	if (buffer[i + 1] == buffer[i] || buffer[i + 1] == ' ')
	{
		i = move_space(buffer, i + 2);
		if (buffer[i] && (buffer[i] == '>' || buffer[i] == '<'))
		{
			ft_putstr_fd("syntax error near unexpected token `", 2);
			if (buffer[i + 1] && (buffer[i + 1] == '>' || buffer[i + 1] == '<'))
				ft_putchar_fd(buffer[i], 2);
			ft_putchar_fd(buffer[i], 2);
			ft_putstr_fd("\'\n", 2);
			return (true);
		}
	}
	return (false);
}

bool	redirect_space_and_count_error(char *buffer)
{
	bool s_quotes;
	bool d_quotes;
	int i;

	s_quotes = false;
	d_quotes = false;
	i = 0;
	while(buffer[i])
	{
		if (buffer[i] == S_QUOTES)
			s_quotes = !s_quotes;
		else if (buffer[i] == D_QUOTES)
			d_quotes = !d_quotes;
		else if ((buffer[i] == '>' || buffer[i] == '<') && (!d_quotes && !s_quotes))
		{
			if (check_valid_redir(buffer, i))
				return (true);
		}
		i++;
	}
	return (false);
}

bool	redirect_error(char *buffer)
{
	bool s_quotes;
	bool d_quotes;
	int i;

	s_quotes = false;
	d_quotes = false;
	i = 0;
	while(buffer[i])
	{
		if (buffer[i] == S_QUOTES)
			s_quotes = !s_quotes;
		else if (buffer[i] == D_QUOTES)
			d_quotes = !d_quotes;
		else if ((buffer[i] == '>' || buffer[i] == '<') && buffer[i + 1] == '\0')
		{
			ft_putstr_fd(ERROR_REDIR, 2);
			ft_putstr_fd("\'\n", 2);
			return (true);
		}
		else if (buffer[i] == '>' && (buffer[move_space(buffer, i + 1)] == '<'
				|| buffer[move_space(buffer, i + 1)] == '|')
				&& !d_quotes && !s_quotes)
		{
			redirect_error_suport(buffer, i);
			return (true);
		}
		i++;
	}
	return (false);
}

bool	redirect_inverse_error(char *buffer)
{
	bool s_quotes;
	bool d_quotes;
	int i;

	s_quotes = false;
	d_quotes = false;
	i = 0;
	while(buffer[i])
	{
		if (buffer[i] == S_QUOTES)
			s_quotes = !s_quotes;
		else if (buffer[i] == D_QUOTES)
			d_quotes = !d_quotes;
		else if (buffer[i] == '<' && (buffer[move_space(buffer, i + 1)] == '>'
				|| buffer[move_space(buffer, i + 1)] == '|')
				&& !d_quotes && !s_quotes && (buffer[i + 1] == ' ' 
				|| buffer[i + 1] == '|'))
		{
			redirect_inverse_error_suport(buffer, i);
			return (true);
		}
		i++;
	}
	return (false);
}