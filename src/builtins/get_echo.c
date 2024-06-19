/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:40:54 by bde-souz          #+#    #+#             */
/*   Updated: 2024/06/19 15:28:23 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	put_token_str(t_token *token, t_data *data)
{
	if (token->str[0] == '~'
		&& (token->str[1] == '\0' || token->str[1] == '/')) //#TODO Revisar essa condicao
	{
		ft_putstr_fd(get_in_env(data->envp, "HOME"), 1);
		ft_putstr_fd(&token->str[1], 1);
		if (token->next)
			write(1, " ", 1);
	}
	else if (token->str[0] == '~'
		&& (token->str[1] == '-' || token->str[1] == '+')) //#TODO Revisar essa condicao
	{
		if (token->str[1] == '+')
			ft_putstr_fd(get_in_env(data->envp, "PWD"), 1);
		else
			ft_putstr_fd(get_in_env(data->envp, "OLDPWD"), 1);
		if (token->next)
			write(1, " ", 1);
	}
	else if (token->next)
	{
		ft_putstr_fd(token->str, 1);
		write(1, " ", 1);
	}
	else
		ft_putstr_fd(token->str, 1);
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

bool	is_all_flag(t_token *token)
{
	int i;

	i = 2;
	if(token->str[0] == '-' && token->str[1] == 'n') //se for "-n..."
	{
		while(token->str[i]) // Enquanto a str existir
		{
			if(token->str[i] == 'n') // se a posicao atual for "n"
				i++;
			else
				return (false); // se for diferente de "n", entao nao e uma flag valida
		}
	}
	else
		return (false); // Se nao for "-n..."
	return (true); // se andou por toda string e nao achou alem de "n"
}


void	get_echo(t_token *token, t_data *data)
{
	int		t_flag;
	
	t_flag = 0;
	while(token)
	{
		if (token->str[0] == '-' && token->str[1] == 'n') // verifica se o node atual e uma "-n"
		{
			if(is_all_flag(token) == true)
			{
				token->type = flag;
				t_flag = 1;
			}
		}
		while (token->type == flag) //Se for uma flag
		{
			token = token->next;
			if (!token)
				break;
			if(is_all_flag(token) == true)
				token->type = flag;
		}
		while (token && (token->type == string
			|| token->type == not_expander || token->type == expander))
		{
			put_token_str(token, data);
			token = token->next;
		}
	}
	if (t_flag == 0)
		write(1, "\n", 1);
	G_EXIT_CODE = 0;
}
