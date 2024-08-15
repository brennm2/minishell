/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:58:45 by bde-souz          #+#    #+#             */
/*   Updated: 2024/08/09 13:04:23 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DESCRIÇÃO: --------------------------
// Verifica se há um caractere alfanumérico

#include "libft.h"

int	ft_isalnum(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}
/*
#include <stdio.h>

int main (void)
{
    char   ch = '5';
    printf("%d\n", ft_isalnum(ch));
    return (5);
}*/
