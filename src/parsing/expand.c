/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:29:01 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/06/03 16:06:17 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_is_especial(int c)
{
	if ((c >= 33 && c <= 47))
		return (1);
	return (0);
}

void	change_token(t_envp *envp, t_token *token, int flag)
{
	char	*expanded;
	
	if (flag == 1)
	{	
		free(token->str);
		token->str = ft_calloc(sizeof(char), (ft_strlen(envp->value) + 1));
		ft_strlcpy(token->str, envp->value, ft_strlen(envp->value) + 1);
		//token->str = expanded;
	}
	if (flag == 0)
	{
		free(token->str);
		token->str = ft_calloc(sizeof(char), 2);
		ft_strlcpy(token->str, "\n", 1);
		//token->str = expanded;
	}
	printf("change_token %s\n", token->str);
}

void	check_env(t_token *token, t_envp *env, int i, int j)
{
	char	*variable;
	int		size;
	int		flag;
	
	size = i - j;
	flag = 0;
	variable = ft_calloc(sizeof(char), size);
	if (!variable)
		exit(1);
	ft_strlcpy(variable, token->str + j + 1, (size));
	//printf("variable is %s\n", variable);
	while (env->next)
	{
		if (!ft_strncmp(variable, env->key, size))
			flag = 1;
		env = env->next;
	}
	change_token(env, token, flag);
	printf("check_env %s\n", token->str);
	free (variable);
}

void	is_expand(t_token *token, t_envp *envp)
{
	int	i;
	int	j;

	i = -1;
	if (token->type == not_expander)
		return ;
	printf("before %s\n", token->str);
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
			//printf("%d %d\n", i, j);
			check_env(token, envp, i, j);
			printf("after %s\n", token->str);
		}
	}
}

void	expand(t_data *data)
{
	while (data->token)
	{
		is_expand(data->token, data->envp);
		data = data->next;
	}
}
