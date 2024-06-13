/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:20:02 by bde-souz          #+#    #+#             */
/*   Updated: 2024/06/13 20:47:41 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	G_EXIT_CODE;

void	search_command(char *buffer, t_data *data)
{
	buffer = check_spaces(buffer);
	get_split(buffer, data);
}

void	use_command(t_data *data)
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
		printf("type: %d\n", data->token->type);
		printf("builtin: %d\n\n\n", data->token->builtin);
		
		data->token = data->token->next;
	}
	printf("Error code: %d\n", G_EXIT_CODE);
	data->token = temp_token;
}

void init_commands(char *buffer, t_data *data)
{
	init_data(data, buffer);
	search_command(buffer, data);
	tokenize(data);
	expand(data);
	remove_quotes(data);
	debug_print_list_ex(data);
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
	int i = 0;
	while(1)
	{
		buffer = readline("minishell: ");
		add_history(buffer);
		if (valid_input(buffer))
		{
			G_EXIT_CODE = 0;
			init_commands(buffer, data);
		}
		//ft_free_data(data, 1);
	}
	//ft_free_data(data, 1);
}

//valgrind --leak-check=full --show-leak-kinds=all --suppressions=supp.supp ./minishell
