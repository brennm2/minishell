/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:22:56 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/05/24 16:23:42 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int				i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if ((int)n < 0)
		return ((int)n);
	while ((str1[i] || str2[i]) && i < (int)n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

void	set_builtins(t_token *token, t_builtins	blt)
{
	token->type = builtin;
	token->builtin = blt;
}

bool	is_builtin(t_token *token)
{
	if (!ft_strncmp(token->str, "echo", 4))
		set_builtins(token, echo);
	else if (!ft_strncmp(token->str, "cd", 2))
		set_builtins(token, cd);
	else if (!ft_strncmp(token->str, "pwd", 3))
		set_builtins(token, pwd);
	else if (!ft_strncmp(token->str, "export", 6))
		set_builtins(token, export);
	else if (!ft_strncmp(token->str, "unset", 5))
		set_builtins(token, unset);
	else if (!ft_strncmp(token->str, "env", 3))
		set_builtins(token, env);
	else if (!ft_strncmp(token->str, "exit", 4))
		set_builtins(token, Exit);
	else 
		return (false);
	return (true);
}

void	define_tokens(t_token *token)
{
	if (!ft_strncmp(token->str, "|", 1) && token->str[1] == '\0')
		token->type = is_pipe;
	else if (!ft_strncmp(token->str, "<", 1) && token->str[1] == '\0')
		token->type = redin;
	else if (!ft_strncmp(token->str, ">", 1) && token->str[1] == '\0')
		token->type = redout;
	else if (!ft_strncmp(token->str, "<", 1) && token->str[1] == '\0')
		token->type = redin;
	else if (!ft_strncmp(token->str, ">>", 1) && token->str[2] == '\0')
		token->type = append;
	else 
		token->type = string;
}

int main(void)
{
	t_token token;
	
	token.str = "|";
	if (is_builtin(&token))
	{
		printf ("Str = %s\nType = %d\nBuiltin = %d\n", token.str, token.type, token.builtin);
	}
	else
	{
		printf("Not a builtin\n");
		define_tokens(&token);
		printf ("Str = %s\nType = %d\n", token.str, token.type);
	}
	return 0;
}