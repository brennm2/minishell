/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:29:49 by bde-souz          #+#    #+#             */
/*   Updated: 2024/07/02 11:57:38 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void	init_next_token(t_token *token, int len)
{
	token->next = (t_token *)ft_calloc(1, sizeof(t_token));
	//token->next->str = NULL;
	token->next->str = ft_calloc(sizeof(char *), len + 1);
}

void	init_token(t_token *token, char *buffer)
{
	token->str = ft_calloc(1, ft_strlen(buffer) + 1);
	//token->next = (t_token *)ft_calloc(1, sizeof(t_token));
}

void init_data(t_data *data, char *buffer)
{
	data->token = (t_token *)ft_calloc(1, sizeof(t_token));
	//data->envp = (t_envp *)ft_calloc(1, sizeof(t_envp));
	//data->next = (t_data *)(ft_calloc(1, sizeof(t_data)));
	init_token(data->token, buffer);
}

void	set_exit_code(int code)
{
	G_EXIT_CODE = code;
}
