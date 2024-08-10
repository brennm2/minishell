/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:22:56 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/08/09 11:19:59 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

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
	else if (token->str && !ft_strncmp(token->str, ">>", 1) && \
	token->str[2] == '\0')
		token->type = append;
}

void	check_tokenize_util(t_data *data)
{
	t_token	*token_aux;

	token_aux = data->token;
	if (token_aux->type == string)
		which_command(token_aux);
	after_pipe(data);
	after_reds(data);
}

void	check_tokenize(t_data *data)
{
	t_token	*token_aux;
	t_token	*first;

	check_tokenize_util(data);
	first = data->token;
	token_aux = data->token;
	while (token_aux)
	{
		if (token_aux->type == is_pipe)
			first = token_aux->next;
		if (is_red_or_pipe(token_aux))
		{
			if ((token_aux->type == redin || token_aux->type == redout \
				|| token_aux->type == append) && first->builtin == echo)
			{
				token_aux = token_aux->next;
				continue ;
			}
			if (token_aux->next && !is_red_or_pipe(token_aux->next))
				which_command(token_aux->next);
		}
		token_aux = token_aux->next;
	}
}

void	tokenize(t_data *data)
{
	t_token	*token_aux;

	token_aux = data->token;
	while (token_aux)
	{
		is_red(token_aux);
		token_aux = token_aux->next;
	}
	token_aux = data->token;
	while (token_aux)
	{
		if (!ft_strcmp(token_aux->str, "|"))
			token_aux->type = is_pipe;
		token_aux = token_aux->next;
	}
	check_tokenize(data);
}
