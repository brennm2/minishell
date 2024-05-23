/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:29:26 by bde-souz          #+#    #+#             */
/*   Updated: 2024/05/23 21:39:21 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/**
 * @brief Função de Debug para imprimir o que está na lista de Token.
 * @param data Estrutura de <DATA> para iterar até chegar ao NULL de data->str
 * @return <VOID>
 */
void	debug_print_list(t_data *data)
{
	int i;

	i = 0;
	while(data->token->str)
	{
		printf(C_BLUE"Node:"END_COLOR C_GREEN" %d "END_COLOR, i++);
		printf(C_RED"-"END_COLOR"%s"C_RED"-\n"END_COLOR, data->token->str);
		data->token = data->token->next;
	}
}