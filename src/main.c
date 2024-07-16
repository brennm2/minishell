/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:20:02 by bde-souz          #+#    #+#             */
/*   Updated: 2024/07/16 16:15:02 by bde-souz         ###   ########.fr       */
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
	//debug_print_list(data);
	is_here_doc(data);
	expand(data);
	tokenize(data);
	remove_quotes(data);
	//debug_print_list(data);
}

void	reset_fd_signals(int fd1, int fd2)
{
	ft_catch_signal(MAIN);
	dup2(fd1, STDIN_FILENO);
	dup2(fd2, STDOUT_FILENO);
}

t_data	*init_minishell(int argc, char **argv, char ** envp, t_data *data)
{	
	if (argc != 1 || argv[1])
	{
		print_error("Minishell does not accept any arguments.", 1, data);
		exit(1);
	}
	data = ft_calloc(1, sizeof(t_data));;
	if (!data)
		print_error("Malloc error.", 1, data);
	get_env(data, envp);
	return (data);
}

void	update_exit_code(int status, t_data *data)
{
	if (WIFEXITED(status))
		set_exit_code(WEXITSTATUS(status), data);
}

bool	is_only_builtin(t_data *data, t_token *token)
{
	(void)data;
	t_token *temp_token;

	temp_token = token;
	while(temp_token)
	{
		if (temp_token->type != builtin && temp_token->type != string)
			return (false);
		temp_token = temp_token->next;
	}
	return (true);
}

void	loop_minishell(int fd1, int fd2, t_data *data)
{
	char	*buffer;
	int		status;

	buffer = NULL;
	data->exit_code = 0;
	while (1)
	{
		reset_fd_signals(fd1, fd2);
		buffer = readline(C_CYAN"minishell: "END_COLOR);
		add_history(buffer);
		if (!valid_input(buffer, data))
			continue ;
		init_commands(buffer, data);
		if (is_only_builtin(data, data->token) == true)
			get_builtin(data, data->token, 0);
		else
		{
			ft_signal_ignore();
			if (safe_fork(data) == 0)
			{
				execution(data);
			}
			waitpid(0, &status, 0);
			update_exit_code(status, data);
		}
		//printf("exit code: %d\n", data->exit_code); //DEBUG
		free_token(data->token);
	}
}

int main(int argc, char **argv, char **envp)
{
	t_data	*data;
	int	fd1;
	int	fd2;

	fd1 = dup(STDIN_FILENO);
	fd2 = dup(1);
	//G_EXIT_CODE = 0; //#TODO <-- Exit code fica aqui?
	data = NULL;
	data = init_minishell(argc, argv, envp, data);
	data->exit_code = 0;
	loop_minishell(fd1, fd2, data);
}

