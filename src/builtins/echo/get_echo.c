/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:40:54 by bde-souz          #+#    #+#             */
/*   Updated: 2024/08/08 21:01:59 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

bool	need_space(t_token *token)
{
	// t_token *temp_token;

	// temp_token = token;

	while (token && (token->type != is_pipe))
	{
		if(token->type == string)
			return (true);
		token = token->next;
	}
	return (false);
}

void	put_token_str(t_token *token, t_data *data)
{
	if (token->str[0] == '~' && (token->str[1] == '-' || token->str[1] == '+'))
	{
		echo_handle_tidle(data, token);
		if (token->next)
			write(1, " ", 1);
	}
	else if (token->next && (token->next->type == string
			|| token->next->type == redin || token->next->type == redout || token->next->type == append))
	{
		ft_putstr_fd(token->str, 1);
		if (need_space(token->next) == true)
			write(1, " ", 1);
	}
	else
		ft_putstr_fd(token->str, 1);
}

int	get_echo_flag(t_token *token)
{
	if (ft_strcmp(token->str, "-n") == 0) //Se a flag for -n
		return (1);
	else
	{
		write(1, token->str, ft_strlen(token->str));
		return (0);
	}
}

bool	is_all_flag(t_token *token)
{
	int	i;

	i = 2;
	if (token->str[0] == '-' && token->str[1] == 'n') //se for "-n..."
	{
		while (token->str[i]) // Enquanto a str existir
		{
			if (token->str[i] == 'n') // se a posicao atual for "n"
				i++;
			else
				return (false); // se for diferente de "n", entao nao e uma flag valida
		}
	}
	else
		return (false); // Se nao for "-n..."
	return (true); // se andou por toda string e nao achou alem de "n"
}

// echo test > ola | oi

void	handle_token(t_token **token, t_data *data)
{
	while (*token && (*token)->type != is_pipe) //((*token)->type == string
			//|| (*token)->type == redin || (*token)->type == redout
			//|| (*token)->type == append))
	{
		//write(2, "a\n", 2);
		if ((*token)->type == redin || (*token)->type == redout || (*token)->type == append)
		{
			*token = (*token)->next;
			if (!(*token) || (*token)->type == is_pipe)
				break ;
			else
				continue;
		}
		//ft_putstr_fd((*token)->str, 2);
		put_token_str(*token, data);
		*token = (*token)->next;
	}
}

void	get_echo(t_token *token, t_data *data, int exit_flag)
{
	int	t_flag;

	t_flag = 0;
	while (token && token->type != is_pipe)//(token->type == string || token->type == command))
	{
		if (token->str[0] == '-' && token->str[1] == 'n'
			&& is_all_flag(token) == true)
		{
			token->type = flag;
			t_flag = 1;
		}
		while (token->type == flag)
		{
			token = token->next;
			if (!token)
				break ;
			if (is_all_flag(token) == true)
				token->type = flag;
		}
		handle_token(&token, data);
		// if (token->type == is_pipe)
		// 	break;
		//ft_putstr_fd(token->str, 2);
		
		//ft_putstr_fd("test\n", 2);
	}
	if (t_flag == 0)
		write(1, "\n", 1);
	ft_exit_flag(0, exit_flag, data);
}
