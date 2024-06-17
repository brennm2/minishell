/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:19:54 by bde-souz          #+#    #+#             */
/*   Updated: 2024/06/17 12:02:04 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	exit_numeric_error(t_data *data)
{
	//bash: exit: 12a: numeric argument required
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(data->token->next->str, 2);
	ft_putstr_fd(": numeric argument required", 2);
	exit (2);
}

void	get_exit(t_data *data)
{
	int i;
	
	i = -1;
	if (!data->token->next->str) //Se for somente "exit"
	{
		printf("exit = %d\n", G_EXIT_CODE); // <-- DEBUGER Retirar
		ft_putstr_fd("exit\n", 1);
		exit (G_EXIT_CODE);
	}
	else if (data->token->next->str) // Se existir <TOKEN->NEXT> / "exit algumacoisa"
	{
		while (ft_isalnum(data->token->next->str[++i]) == 1) // Se <TOKEN->STR> for somente numeros
		{
			i++;
			if(data->token->next->str[i] == '\0') // Se <TOKEN->STR> acabar e for tudo numero
			{
				printf("exit = %d\n", G_EXIT_CODE); // <-- DEBUGER Retirar
				ft_putstr_fd("exit\n", 1);
				exit(ft_atoi(data->token->next->str));
			}
		}
		//Se saiu do loop entao encotrou algo que nao e numerico
		exit_numeric_error(data);
		
		
		//#TODO Verificar tudo isso pq esta ruim em!
		printf("nao e numero burro\n");
		exit;
	}
	
	
	
	//#TODO Fazer a func get_exit
}