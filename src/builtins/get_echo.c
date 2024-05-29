/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:40:54 by bde-souz          #+#    #+#             */
/*   Updated: 2024/05/29 13:36:25 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_strcmp(char *s1, char *s2) // apagar
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void	put_token_str(t_token *token)
{
	if (token->next->str)
	{
		write(1, token->str, ft_strlen(token->str));
		write(1, " ", 1);
	}
	else
			write(1, token->str, ft_strlen(token->str));
}

int	get_echo_flag(t_token *token)
{
	if(ft_strcmp(token->str, "-n") == 0) //Se a flag for -n
		return (1);
	else
	{
		write(1, token->str, ft_strlen(token->str));
		return (0);
	}
}


void	get_echo(t_token *token)
{
	t_token	*reset_token;
	int		t_flag;
	
	t_flag = 0;
	reset_token = token;
	while(token->str)
	{
		// Cuidado com a flag!
		if (ft_strcmp(token->str, "-n") == 0) // retirar isso
			token->type = flag;
		if (token->type == flag) //Se for uma flag
		{
			t_flag = get_echo_flag(token);
			token = token->next;
		}
		else if (token->type == string || token->type == not_expander
			|| token->type == expander)
		{
			put_token_str(token);
			token = token->next;
		}
	}
	if (t_flag == 0)
		write(1, "\n", 1);
	// Voltar com a lista para o comeco?
	// Limpar a lista?
}
