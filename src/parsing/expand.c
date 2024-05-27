/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:29:01 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/05/27 17:48:42 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/* void	is_expand(t_token *token, t_data *data) */

int	ft_isupper(int c)
{
	if ((c >= 65 && c <= 90))
		return (1);
	return (0);
}

void	is_expand(char *token)
{
	int	i;
	int	j;

	i = -1;
	/* if (token->type == not_expander)
		return ; */
	while (token[++i])
	{
		if (token[i] == '$')
		{
			j = i;
			if (token[i + 1] == '?')
				printf("error\n");
			while (ft_isupper(token[++i]))
				;
			printf("%d, %d\n", j, (i - 1));
		}
	}
}

int main(int ac, char **av, char **envp)
{
	char *token;
	//t_data *data;
	
	token = "aaaa$aUSERRRaaa'";
	//get_env(&data, envp);
	is_expand(token);
	return (0);
}