/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:20:02 by bde-souz          #+#    #+#             */
/*   Updated: 2024/07/08 10:43:45 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	G_EXIT_CODE;

void	search_command(char *buffer, t_data *data)
{
	buffer = check_spaces(buffer);
	get_split(buffer, data);
	free(buffer);
}

/* void	use_command(t_data *data, t_token *token)
{
	if(token->type == builtin)
		get_builtin(data);
	else
		cmd_execution(data);
} */

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
/* 	if (is_here_doc(data))
		return ; */
	expand(data);
	tokenize(data);
	remove_quotes(data);
	//debug_print_list(data);
	//use_command(data, data->token);
	//free_token(data->token);
}

void	reset_fd_signals(int fd1, int fd2)
{
	ft_catch_signal(MAIN);
	dup2(fd1, STDIN_FILENO);
	dup2(fd2, STDOUT_FILENO);
}

int main(int argc, char **argv, char **envp)
{
	char	*buffer;
	t_data	*data;
	int		status;

	int	fd1;
	int	fd2;

	//
	fd1 = dup(STDIN_FILENO);
	fd2 = dup(1);
	//
	
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
		reset_fd_signals(fd1, fd2);
		buffer = readline(C_CYAN"minishell: "END_COLOR);
		add_history(buffer);
		if (!valid_input(buffer, data))
			get_exit(data);
		init_commands(buffer, data);
		if (safe_fork(data) == 0)
			execution(data);
		waitpid(0, &status, 0);
		free_token(data->token);
	}
}

