/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:20:02 by bde-souz          #+#    #+#             */
/*   Updated: 2024/06/03 11:41:16 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	G_EXIT_CODE;

void	search_command(char *buffer, t_data *data) // FUNC separar o buffer em tokens
{
	get_split(buffer, data);
	//debug_print_list(data); // DEBUG PARA LER A LISTA COMPLETA
	//free_all(data);
}

void	use_command(t_data *data) // Func para buscar qual tipo de <type>
{
	if(data->token->type == builtin)
		get_builtin(data);
}

void init_commands(char *buffer, t_data *data)
{
	int i;

	i = 0;
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
	

	data = ft_calloc(1, sizeof(t_data));;
	if (!data)
		return (0);
	get_env(data, envp);
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
