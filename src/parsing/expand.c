/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:29:01 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/06/14 14:31:32 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int ft_is_especial(int c)
{
	if ((c >= 33 && c <= 47))
		return (1);
	return (0);
}

char	*ft_strjoin_ex(char *s1, char const *s2)
{
	int		strlen;
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	strlen = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (strlen + 1));
	if (!str)
		return (NULL);
	while (s1 && s2)
	{
		while (s1[i])
			str[j++] = s1[i++];
		i = 0;
		while (s2[i])
			str[j++] = s2[i++];
		str[j] = '\0';
		free(s1);
		return (str);
	}
	return (NULL);
}

void expanded(t_envp *envp, t_token *token, char *variable, int flag)
{
	char *expanded;
	int i;
	
	i = -1;
	while (token->str[++i] != '$')
		;
	expanded = ft_calloc(sizeof(char *), i + 1);
	ft_strlcpy(expanded, token->str, i + 1);
	if (flag == 1)
		expanded = ft_strjoin_ex(expanded, envp->value);
	expanded = ft_strjoin_ex(expanded, token->str + i + 1 + ft_strlen(variable));
	free(token->str);
	token->str = expanded;
}

void check_env(t_token *token, t_envp *env, int i, int j)
{
	char *variable;
	int size;
	t_envp *env_aux;

	env_aux = env;
	size = i - j;
	variable = ft_calloc(sizeof(char), size + 1);
	if (!variable)
		exit(1);
	ft_strlcpy(variable, token->str + j + 1, (size));
	while (env_aux)
	{
		if (!ft_strncmp(variable, env_aux->key, size))
		{
			expanded(env_aux, token, variable, 1);
			free(variable);
			return ;
		}
		env_aux = env_aux->next;
	}
	expanded(NULL, token, variable, 0);
	free(variable);
}

void is_expand(t_token *token, t_envp *envp)
{
	int i;
	int j;

	i = -1;
	if (token->type == not_expander)
		return;
	while (token->str[++i])
	{
		if (token->str[i] == '$')
		{
			j = i;
			if (token->str[i + 1] == '?') //Modificado para imprimir o que esta na variavel G_EXIT_CODE
			{
				free(token->str); // Limpa o que esta no <TOKEN->STR>
				token->str = ft_strdup(ft_itoa(G_EXIT_CODE)); // Aloca e coloca o G_EXIT_CODE no <TOKEN->STR>
				//printf("error\n");
				return;
			}
			while (!ft_is_especial(token->str[++i]) && token->str[i])
				;
			check_env(token, envp, i, j);
			i = -1;
		}
	}
}

void expand(t_data *data)
{
	t_token *token_aux;

	token_aux = data->token;
	while (token_aux->next)
	{
		is_expand(token_aux, data->envp);
		token_aux = token_aux->next;
	}
}
