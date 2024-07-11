/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:45:52 by bde-souz          #+#    #+#             */
/*   Updated: 2024/07/11 12:19:55 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	get_pwd(t_token *token, t_data *data)
{
	char	pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	if (token->next)
	{
		if (token->next->str[0] == '-')
		{
			write(2, "minishell: pwd: -", 17);
			write(2, &token->next->str[1], 1);
			write(2, ": invalid option\n", 17);
			print_error(NULL, 2, data);
			return ;
		}
	}
	ft_putstr_fd(pwd, 1);
	ft_putchar_fd('\n', 1);
	return (set_exit_code(0, data));
}
