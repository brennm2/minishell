/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:29:01 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/06/13 16:50:38 by nsouza-o         ###   ########.fr       */
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
	int j;
	
	i = -1;
	while (token->str[++i])
	{
		if (token->str[i] == S_QUOTES)
			i = deal_with_quotes(token, i, envp);
		if (token->str[i] == '$')
		{
			j = i;
			while (!ft_is_especial(token->str[++i]) && token->str[i])
				;
			break;
		}
	}
	expanded = ft_calloc(sizeof(char *), j + 1);
	ft_strlcpy(expanded, token->str, j + 1);
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

bool	check_for_quotes_expander(char *buffer, int i)
{
	bool	dquotes;
	bool 	squotes;

	dquotes = false;
	squotes = false;

	while(i >= 0 && buffer[i])
	{
		if(buffer[i] == S_QUOTES && dquotes == false)
			squotes = !squotes;
		if(buffer[i] == D_QUOTES && squotes == false)
			dquotes = !dquotes;
		i--;
	}
	if (squotes == true)
		return (true);
	else
		return (false);
}
int	deal_with_quotes(t_token *token, int i, t_envp *envp)
{
	int	j;
	
	if (token->str[i] == S_QUOTES)
	{
		i++;
		while (token->str[i] != S_QUOTES)
			i++;
	}
	/* else
	{
		i++;
		while (token->str[i] != S_QUOTES)
		{
			if (token->str[i] == '$')
			{
				j = i;
				if (token->str[i + 1] == '?')
				{
					printf("error\n");
					return (i + 2);
				}
				while (!ft_is_especial(token->str[++i]) && token->str[i])
					;
				check_env(token, envp, i, j);
			}
			i++;
		}
	} */
	return (i);
}

void is_expand(t_token *token, t_envp *envp)
{
	int i;
	int j;
	bool	status;
	
	status = true;
	i = -1;
	while (token->str[++i])
	{
		if (token->str[i] == S_QUOTES)
			i = deal_with_quotes(token, i, envp);
		if (token->str[i] == '$')
		{
			j = i;
			if (token->str[i + 1] == '?')
			{
				printf("error\n");
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
