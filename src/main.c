/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:20:02 by bde-souz          #+#    #+#             */
/*   Updated: 2024/06/06 19:39:27 by nsouza-o         ###   ########.fr       */
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

void	debug_print_list_ex(t_data *data)
{
	int			i;
	t_token		*temp_token;

	i = 0;
	temp_token = data->token;
	while (data->token->str)
	{
		printf(C_BLUE"Node:"END_COLOR C_GREEN" %d "END_COLOR, i++);
		printf(C_RED"-"END_COLOR"%s"C_RED"-\n"END_COLOR, data->token->str);
		/* printf("type: %d\n", data->token->type);
		printf("builtin: %d\n\n\n", data->token->builtin); */
		
		data->token = data->token->next;
	}
	printf("Error code: %d\n", G_EXIT_CODE);
	data->token = temp_token;
}

void init_commands(char *buffer, t_data *data)
{
	init_data(data, buffer);
	search_command(buffer, data);
	expand(data);
	debug_print_list_ex(data);
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
	/* i = 0;
	int i;
	while (data->envp)
	{
		printf("%d %s = %s\n", i, data->envp->key, data->envp->value);
		printf("-\n"),
		data->envp = data->envp->next;
		i++;
	} */
