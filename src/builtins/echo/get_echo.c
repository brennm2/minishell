/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:40:54 by bde-souz          #+#    #+#             */
/*   Updated: 2024/07/12 15:44:15 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	put_token_str(t_token *token, t_data *data)
{
	if (token->str[0] == '~'
		&& (token->str[1] == '-' || token->str[1] == '+'))
	{
		if (token->str[1] == '+')
			ft_putstr_fd(get_in_env(data->envp, "PWD"), 1);
		else
			ft_putstr_fd(get_in_env(data->envp, "OLDPWD"), 1);
		if (token->next)
			write(1, " ", 1);
	}
	else if (token->next && token->next->type == string)
	{
		ft_putstr_fd(token->str, 1);
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

// void	handle_token(t_token **token, t_data *data)
// {
// 	while (*token && ((*token)->type == string || (*token)->type == not_expander
// 			|| (*token)->type == expander))
// 	{
// 		put_token_str(*token, data);
// 		*token = (*token)->next;
// 	}
// }

void	handle_token(t_token **token, t_data *data)
{
	while (*token && ((*token)->type == string))
	{
		put_token_str(*token, data);
		*token = (*token)->next;
	}
}

void	get_echo(t_token *token, t_data *data, int exit_flag)
{
	int	t_flag;

	//write (1, "B\n", 2);
	t_flag = 0;
	while (token && token->type == string)
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
	}
	if (t_flag == 0)
		write(1, "\n", 1);
	ft_exit_flag(0, exit_flag, data);
}
