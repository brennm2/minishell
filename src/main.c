/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:20:02 by bde-souz          #+#    #+#             */
/*   Updated: 2024/07/02 10:45:47 by nsouza-o         ###   ########.fr       */
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
	else
		command_not_found(data->token);
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
	/* if (is_here_doc(data))
		return ; */
	expand(data);
	remove_quotes(data);
	tokenize(data);
	//debug_print_list(data);
	//use_command(data);
	/* if (safe_fork(data) == 0)
		execution(data); */
}

/* void	init_loop(t_data *data)
{
	char	*buffer;
	int		status;
	
	while(1)
	{
		buffer = NULL;
		buffer = readline(C_CYAN"minishell: "END_COLOR);
		add_history(buffer);
		if (!valid_input(buffer))
		{
			free(buffer);
			continue;
		}
		init_commands(buffer, data);
		if (safe_fork(data) == 0)
			execution(data);
		free(buffer);
		clear_history();
		waitpid(0, &status, 0);
		//printf("Exit code: %d\n", G_EXIT_CODE); //DEBUGGER
		
		//ft_free_data(data, 1);
	}
}

int main(int argc, char **argv, char **envp)
{
	t_data	*data;
	
	if (argc > 1 || argv[1])
	{
		print_error("Inputs are not being received by Minishell.", 1);
		clean(NULL, 1);
	}
	data = ft_calloc(1, sizeof(t_data));;
	if (!data)
		print_error("Malloc error! \n", 1);
	get_env(data, envp);
	G_EXIT_CODE = 0;
	init_loop(data);
	clean(data, 0);
} */


int main(int argc, char **argv, char **envp)
{
	char	*buffer;
	t_data	*data;
	
	(void)argc;
	(void)argv;

	buffer = NULL;
	data = ft_calloc(1, sizeof(t_data));;
	if (!data)
		return (0);
	get_env(data, envp);
	G_EXIT_CODE = 0; //#TODO <-- Exit code fica aqui?
	while(1)
	{
		buffer = readline(C_CYAN"minishell: "END_COLOR);
		add_history(buffer);
		if (valid_input(buffer))
		{
			init_commands(buffer, data);
			//free(buffer);
			//debug_print_list(data);
			if (safe_fork(data) == 0)
				execution(data);
			//free_token(data->token);
		}
		free(buffer);
		waitpid(0, NULL, 0);
		//printf("Exit code: %d\n", G_EXIT_CODE); //DEBUGGER
		
		//ft_free_data(data, 1);
	}
	//ft_free_data(data, 1);
}
//valgrind --leak-check=full --show-leak-kinds=all --suppressions=supp.supp ./minishell
