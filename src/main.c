/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:20:02 by bde-souz          #+#    #+#             */
/*   Updated: 2024/05/28 17:07:49 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	G_EXIT_CODE;

void	search_command(char *buffer, t_data *data)
{
	get_split(buffer, data);
	//debug_print_list(data); // DEBUG PARA LER A LISTA COMPLETA
	//free_all(data);
}

void	use_command(t_data *data)
{
	if(data->token->type == builtin)
		get_builtin(data);
}

void init_commands(char *buffer, t_data *data)
{
	init_data(data, buffer);
	search_command(buffer, data);
	data->token->type = builtin; // retirar
	data->token->builtin = echo;// retirar
	use_command(data);
}

int main(int argc, char **argv, char **envp)
{
	char	*buffer;
	t_data	*data;
	

	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	while(1)
	{
		buffer = readline("minishell: ");
		add_history(buffer);
		if (valid_input(buffer))
		{
			init_commands(buffer, data);
		}
		//printf("$?: %d\n", G_EXIT_CODE); //<-- verificar o ultimo exit code
	}
}
