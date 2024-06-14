/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:45:52 by bde-souz          #+#    #+#             */
/*   Updated: 2024/06/14 10:50:31 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	get_pwd(t_token *token)
{
	char pwd[PATH_MAX];
	getcwd(pwd, sizeof(pwd));
	if (token->next->str != NULL) //Se houver algo alem de somente "pwd"
	{
		if (token->next->str[0] == '-') //Se existir o proximo node for <TYPE> flag
		{
			write(2, "minishell: pwd: -", 17);
			write(2, &token->next->str[1], 1); //Imprimir so o comeco da flag
			write(2, ": invalid option\n", 17);
			print_error(NULL, 2); //Entrar como NULL para guardar somente o exit code
			return ;
		}
	}
	ft_putstr_fd(pwd, 1);
	//write(1, pwd, ft_strlen(pwd));
	ft_putchar_fd('\n', 1);
	return (set_exit_code(0));
}
