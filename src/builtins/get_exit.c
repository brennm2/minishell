/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:19:54 by bde-souz          #+#    #+#             */
/*   Updated: 2024/06/14 14:58:51 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	get_exit(t_data *data)
{
	int i;
	
	i = 0;
	if (!data->token->next->str)
	{
		printf("exit = %d\n", G_EXIT_CODE); // <-- DEBUGER Retirar
		exit (G_EXIT_CODE);
	}
	else if (data->token->next->str) // Se existir <TOKEN->NEXT>
	{
		while (ft_isalnum(data->token->next->str[i])) // Se <TOKEN->STR> for somente numeros
		{
			i++;
			if(data->token->next->str[i]) // Se <TOKEN->STR> acabar e for tudo numero
				exit(ft_atoi(data->token->next->str));
		}
		//#TODO Verificar tudo isso pq esta ruim em!
		printf("nao e numero burro\n");
		exit;
	}
	
	
	
	//#TODO Fazer a func get_exit
}