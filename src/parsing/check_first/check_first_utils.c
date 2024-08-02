/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_first_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:11:10 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/08/02 11:13:03 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	redirect_error_suport(char *buffer, int i)
{
	if (buffer[move_space(buffer, i + 1)] == '<')
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putchar_fd(buffer[move_space(buffer, i + 1)], 2);
		ft_putstr_fd("\'\n", 2);
	}
	else if (buffer[move_space(buffer, i + 1)] == '|')
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putchar_fd(buffer[move_space(buffer, i + 1)], 2);
		ft_putstr_fd("\'\n", 2);
	}
}

void	redirect_inverse_error_suport(char *buffer, int i)
{
	if (buffer[move_space(buffer, i + 1)] == '>')
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putchar_fd(buffer[move_space(buffer, i + 1)], 2);
		ft_putstr_fd("\'\n", 2);
	}
	else if (buffer[move_space(buffer, i + 1)] == '|')
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putchar_fd(buffer[move_space(buffer, i + 1)], 2);
		ft_putstr_fd("\'\n", 2);
	}
}

bool	is_all_space(char *buffer)
{
	int i;

	i = -1;
	while(buffer[++i])
		if (buffer[i] != ' ' && buffer[i] != '\0')
			return (false);
	return (true);
}

bool	first_character(char *buffer)
{
	if (ft_strchr("|<>", buffer[0]) && is_all_space(buffer))
	{
		return (true);
	}
	return (false);
}

