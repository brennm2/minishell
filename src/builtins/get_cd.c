/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:50:20 by bde-souz          #+#    #+#             */
/*   Updated: 2024/06/03 14:17:09 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	get_cd(t_token *token)
{
	//#TODO Fazer o get_cd
	char	cwd[256];

	getcwd(cwd, sizeof(cwd));
	printf("current working directory is: %s\n", cwd);
	//printf("This is a cd\n");
}


// #define _POSIX_SOURCE
// #include <unistd.h>
// #undef _POSIX_SOURCE
// #include <stdio.h>

// main() {
//   char cwd[256];

//   if (chdir("/tmp") != 0)
//     perror("chdir() error()");
//   else {
//     if (getcwd(cwd, sizeof(cwd)) == NULL)
//       perror("getcwd() error");
//     else
//       printf("current working directory is: %s\n", cwd);
//   }
// }