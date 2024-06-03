/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:29:01 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/05/28 17:39:53 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_is_especial(int c)
{
	if ((c >= 33 && c <= 47))
		return (1);
	return (0);
}

char	*check_env(char *str, t_envp *env, int i, int j)
{
	char	*variable;
	int		size;
	
	while (env)
	{
		printf("%s\n", env->key);
		env = env->next;
	}
	printf("---a\n");
	size = i - j;
	variable = ft_calloc(sizeof(char), size);
	if (!variable)
	{
		exit(1);
	}
	ft_strlcpy(variable, str + j + 1, (size));
	printf("%s\n", variable);
	while (env->next)
	{
		if (!ft_strncmp(variable, env->key, size));
		{
			printf("%s\n", env->key);
			free (variable);
			return (env->key);
		}
		env = env->next;
	}
	free (variable);
	return (NULL);
}

void	is_expand(t_token *token, t_data *data)
{
	int	i;
	int	j;

	i = -1;
	if (token->type == not_expander)
		return ;
	//printf("%s\n", data->envp->)
	while (token->str[++i])
	{
		if (token->str[i] == '$')
		{
			j = i;
			if (token->str[i + 1] == '?')
			{
				printf("error\n");
				return ;	
			}
			while (!ft_is_especial(token->str[++i]) && token->str[i])
				;
			check_env(token->str, data->envp, i, j);
		}
	}
}

void	expand(t_data *data)
{
	while (data->envp)
	{
		printf("%s\n", data->envp->key);
		data->envp = data->envp->next;
	}
}
