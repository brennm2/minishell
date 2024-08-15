/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_export_utils_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:10:58 by bde-souz          #+#    #+#             */
/*   Updated: 2024/08/14 16:22:08 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	print_error_option_export(t_token *token)
{
	ft_putstr_fd("minishell: export: -", 2);
	ft_putchar_fd(token->next->str[1], 2);
	ft_putstr_fd(": invalid option\n", 2);
	return ;
}

bool	check_invalid_token(t_token *token)
{
	while (token->next && token->next->type == string)
	{
		if (!is_invalid_token(token->next->str))
			return (true);
		token = token->next;
	}
	return (false);
}
