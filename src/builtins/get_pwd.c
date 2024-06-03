/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:45:52 by bde-souz          #+#    #+#             */
/*   Updated: 2024/06/03 10:54:33 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	get_pwd(t_token *token)
{
	char pwd[PATH_MAX];
	getcwd(pwd, sizeof(pwd));
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
}