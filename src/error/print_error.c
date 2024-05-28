/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:33:40 by bde-souz          #+#    #+#             */
/*   Updated: 2024/05/28 13:54:18 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	print_error(char *error_type, int error_code)
{
	write(2, "minishell: ", 12);
	write(2, error_type, ft_strlen(error_type));
	write(2, "\n", 1);
	G_EXIT_CODE = error_code;
	
} 