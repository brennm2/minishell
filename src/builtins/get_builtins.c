/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:36:06 by bde-souz          #+#    #+#             */
/*   Updated: 2024/05/28 17:07:28 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_strcmp(char *s1, char *s2) // apagar
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void	get_echo(t_data *data)
{
	t_token	*reset_token;
	int		t_flag;
	
	t_flag = 0;
	reset_token = data->token;
	data->token = data->token->next;
	while(data->token->str)
	{
		// CUidado com a flag!
		if (ft_strcmp(data->token->str, "-n") == 0) // retirar isso
			data->token->type = flag;
		if (data->token->type == flag)
		{
			if(ft_strcmp(data->token->str, "-n") == 0)
				t_flag = 1;
			data->token = data->token->next;
		}
		else if (data->token->type == string)
		{
			if (data->token->next)
			{
				write(1, data->token->str, ft_strlen(data->token->str));
				write(1, " ", 1);
			}
			else
				write(1, data->token->str, ft_strlen(data->token->str));
			data->token = data->token->next;
		}
	}
	if (t_flag == 0)
		write(1, "\n", 1);
	// Voltar com a lista para o comeco?
}

void	get_builtin(t_data *data)
{
	//printf("oi");
	if(data->token->builtin == echo)
		get_echo(data);
}



// void	getPWD(t_data *data)
// {
// 	char PWD[PATH_MAX];
// 	getcwd(PWD, sizeof(PWD));
// 	printf("%s\n", PWD);
// 	free(data->token);
// }

// void	getCD(t_data *data)
// {
// 	printf("this is a cd\n");
// 	free(data->token);
// }

// void	getECHO(t_data *data)
// {
// 	t_token *temp_data;

// 	temp_data = data->token;

// 	while(data->token->value != NULL)
// 	{
// 		// se tiver -n
// 			//
// 		printf("%s ", data->token->value);
// 		data->token = data->token->next;
// 	}
// 	printf("\n");
// 	//free(data->command);
// }