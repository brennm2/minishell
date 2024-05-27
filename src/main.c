/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:20:02 by bde-souz          #+#    #+#             */
/*   Updated: 2024/05/27 14:44:48 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	search_command(char *buffer, t_data *data)
{
	get_split(buffer, data);
	debug_print_list(data); // DEBUG PARA LER A LISTA COMPLETA
	//free_all(data);
}

// void	define_type(t_data *data)
// {
// 	if (strcmp(data->token->command, "pwd") == 0)
// 		getPWD(data);
// 	else if (strcmp(data->token->command, "cd") == 0)
// 		getCD(data);
// 	else if (strcmp(data->token->command, "echo") == 0)
// 		getECHO(data);
// 	else if (strcmp(data->token->command, "exit") == 0)
// 		exit(1);
// 	else
// 	{
// 		printf("%s: command not found\n", data->token->command);
// 		//EXIT CODE CERTO;
// 		free(data->token);
// 	}



// void	define_type(t_data *data)
// {
// 	if (strcmp(data->token->command, "pwd") == 0)
// 		getPWD(data);
// 	else if (strcmp(data->token->command, "cd") == 0)
// 		getCD(data);
// 	else if (strcmp(data->token->command, "echo") == 0)
// 		getECHO(data);
// 	else if (strcmp(data->token->command, "exit") == 0)
// 		exit(1);
// 	else
// 	{
// 		printf("%s: command not found\n", data->token->command);
// 		//EXIT CODE CERTO;
// 		free(data->token);
// 	}
// }


void init_commands(char *buffer, t_data *data)
{
	init_data(data, buffer);
	search_command(buffer, data);
	//define_type(data);
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
		//TODO Adicionar func de verificar se pode continuar
		add_history(buffer);
		if (valid_input(buffer))
		{
			init_commands(buffer, data);
		}
	}
} 	