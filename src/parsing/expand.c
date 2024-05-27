/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:29:01 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/05/27 19:22:49 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_isupper(int c)
{
	if ((c >= 65 && c <= 90))
		return (1);
	return (0);
}

char	*check_env(char *str, t_envp *env, int i, int j)
{
	char	*variable;
	
	variable = malloc(j - i);
	ft_strlcpy(variable, str + j, (j - i));
	
	
}

void	is_expand(t_token *token, t_data *data)
{
	int	i;
	int	j;

	i = -1;
	if (token->type == not_expander)
		return ;
	while (token->str[++i])
	{
		if (token->str[i] == '$')
		{
			j = i;
			if (token->str[i + 1] == '?')
				printf("error\n");
			while (ft_isupper(token->str[++i]))
				;
			check_env(token->str, data->envp, i, j);
			//printf("%d, %d\n", j, (i - 1));
		}
	}
}
