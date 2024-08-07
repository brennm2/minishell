/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:29:26 by bde-souz          #+#    #+#             */
/*   Updated: 2024/08/07 13:45:12 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_data	*debug_get_builtin_type(t_data *data)
{
	if(!ft_strcmp(data->token->str, "cd"))
		data->token->builtin = cd;
	else if(!ft_strcmp(data->token->str, "echo"))
		data->token->builtin = echo;
	else if(!ft_strcmp(data->token->str, "env"))
		data->token->builtin = env;
	else if(!ft_strcmp(data->token->str, "pwd"))
		data->token->builtin = pwd;
	else if(!ft_strcmp(data->token->str, "exit"))
		data->token->builtin = n_exit;
	return (data);
}

void	debug_print_list(t_data *data)
{
	int			i;
	t_token		*temp_token;

	i = 0;
	temp_token = data->token;
	while (data->token)
	{
		printf(C_BLUE"Node:"END_COLOR C_GREEN" %d "END_COLOR, i++);
		printf(C_RED"-"END_COLOR"%s"C_RED"-"END_COLOR, data->token->str);
		printf("\n");
		printf("type: %d\n", data->token->type);
		printf("builtin: %d\n\n\n", data->token->builtin);
		
		data->token = data->token->next;
	}
	//printf("Error code: %d\n", G_EXIT_CODE);
	data->token = temp_token;
}
