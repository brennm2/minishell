/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:57:06 by bde-souz          #+#    #+#             */
/*   Updated: 2024/05/24 11:05:13 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/**
 * @brief Itera buffer para dentro da <DATA->TOKEN->STR> e, caso exista buffer,
 * cria mais uma lista usando <DATA->TOKEN->NEXT>
 * @param buffer BUFFER da string
 * @param start START da string para ser salva
 * @param end END da string para ser salva
 * @param data Estrutura de <DATA>
 * @return <VOID>
 */
void	save_substring(char *buffer, int start, int end, t_data *data)
{
	int	i;

	i = 0;
	while(start <= end)
		data->token->str[i++] = buffer[start++];
	if(buffer[start] == D_QUOTES || buffer[start] == S_QUOTES)
		start++;
	if(buffer[start])
	{
		data->token = data->token->next;
		init_token(data->token, buffer);
	}
}


/**
 * @brief Função para executar o split dos comandos.
 * @param buffer String de buffer para ser "splitado"
 * @param data A Estrutura de <DATA> para ser utilizada
 * @return <VOID>
 */
void	get_split(char *buffer, t_data *data)
{
	t_token	*reset_index;
	int		i;

	reset_index = data->token;
	i = 0;
	while(buffer[i])
	{
		if (buffer[i] && (buffer[i] >= 7 && buffer[i] <= 32))
			i = move_space(buffer, i);
		{
			if(buffer[i] == D_QUOTES)
				i = move_with_quotes(buffer, i, D_QUOTES, data);
			if (buffer[i] == S_QUOTES)
				i = move_with_quotes(buffer, i, S_QUOTES, data);
			if (buffer[i] && !(buffer[i] >= 7 && buffer[i] <= 32))
				i = move_without_quotes(buffer, i, data);
		}
	}
	data->token = reset_index;
}
