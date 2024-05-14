/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:36:06 by bde-souz          #+#    #+#             */
/*   Updated: 2024/05/14 14:39:46 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"


void	getPWD(void)
{
	char PWD[PATH_MAX];
	getcwd(PWD, sizeof(PWD));
	printf("%s\n", PWD);
}