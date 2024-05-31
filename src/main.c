/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:20:02 by bde-souz          #+#    #+#             */
/*   Updated: 2024/05/31 16:19:00 by nsouza-o         ###   ########.fr       */
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


void init_commands(char *buffer, t_data *data, char **envp)
{
	int i;

	i = 0;
	init_data(data, buffer);
	search_command(buffer, data);
	get_env(data, envp);
	/* while (data->envp)
	{
		printf("%d %s = %s\n", i, data->envp->key, data->envp->value);
		printf("-\n"),
		data->envp = data->envp->next;
		i++;
	} */
	/* data->token->type = builtin; // retirar
	data->token->builtin = echo;// retirar
	use_command(data); */
}

int main(int argc, char **argv, char **envp)
{
	char	*buffer;
	t_data	*data;
	

	data = ft_calloc(1, sizeof(t_data));;
	if (!data)
		return (0);
	while(1)
	{
		buffer = readline("minishell: ");
		add_history(buffer);
		init_commands(buffer, data, envp);
		//printf("%s\n", data->envp->key);
		//expand(data);
	}
} 	