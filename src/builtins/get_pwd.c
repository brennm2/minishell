/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:45:52 by bde-souz          #+#    #+#             */
/*   Updated: 2024/06/03 13:34:31 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	get_pwd(t_token *token)
{
	char pwd[PATH_MAX];
	getcwd(pwd, sizeof(pwd));
	if (token->next != NULL)
	{
		if (token->next->type == flag) //Se existir o proximo node for <TYPE> flag
		{
			write(2, "minishell: pwd: -", 17);
			write(2, &token->next->str[1], 1); //Imprimir so o comeco da flag
			write(2, ": invalid option\n", 17);
			print_error(NULL, 2); //Entrar como NULL para guardar somente o exit code
			return ;
		}
	}
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
}