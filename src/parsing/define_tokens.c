/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:22:56 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/06/25 16:18:08 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	set_builtins(t_token *token, t_builtins	blt)
{
	token->type = builtin;
	token->builtin = blt;
}

void	which_command(t_token *token)
{
	if (!ft_strncmp(token->str, "echo", 5))
		return (set_builtins(token, echo));
	else if (!ft_strncmp(token->str, "cd", 3))
		return (set_builtins(token, cd));
	else if (!ft_strncmp(token->str, "pwd", 4))
		return (set_builtins(token, pwd));
	else if (!ft_strncmp(token->str, "export", 6))
		return (set_builtins(token, export));
	else if (!ft_strncmp(token->str, "unset", 5))
		return (set_builtins(token, unset));
	else if (!ft_strncmp(token->str, "env", 3))
		return (set_builtins(token, env));
	else if (!ft_strncmp(token->str, "exit", 4))
		return (set_builtins(token, n_exit));
	else
	{
		set_builtins(token, not_builtin);
		token->type = command;
	}
}

void	define_tokens(t_token *token)
{
	if (token->str && !ft_strncmp(token->str, "|", 1))
		token->type = is_pipe;
	else if (token->str && !ft_strncmp(token->str, "<", 1) && \
	token->str[1] == '\0')
		token->type = redin;
	else if (token->str && !ft_strncmp(token->str, ">", 1) && \
	token->str[1] == '\0')
		token->type = redout;
	else if (token->str && !ft_strncmp(token->str, "<", 1) && \
	token->str[1] == '\0')
		token->type = redin;
	else if (token->str && !ft_strncmp(token->str, ">>", 1) && \
	token->str[2] == '\0')
		token->type = append;
	else if (token->str && !ft_strncmp(token->str, "<<", 1) && \
	token->str[2] == '\0')
		token->type = here_doc;
	else
		token->type = string;
}

void	after_pipe(t_data *data)
{
	t_token	*token_aux;

	token_aux = data->token;
	while (token_aux)
	{
		if (token_aux->type == is_pipe)
		{
			token_aux = token_aux->next;
			which_command(token_aux);
		}
		token_aux = token_aux->next;
	}
}

void	tokenize(t_data *data)
{
	t_token	*token_aux;
	int		i;

	i = -1;
	token_aux = data->token;
	while (token_aux)
	{
		if (++i == 0)
		{
			if (!ft_strncmp(token_aux->str, "<", 1))
			{
				token_aux->type = redin;
				token_aux = token_aux->next;
				token_aux = token_aux->next;		
			}
			which_command(token_aux);
		}
		else
			define_tokens(token_aux);
		token_aux = token_aux->next;
	}
	after_pipe(data);
	after_reds(data);
}
