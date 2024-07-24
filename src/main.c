/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:20:02 by bde-souz          #+#    #+#             */
/*   Updated: 2024/07/24 15:47:23 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	G_EXIT_CODE;

void	init_commands(char *buffer, t_data *data)
{
	ft_signal_ignore();
	init_data(data, buffer);
	search_command(buffer, data);
	//debug_print_list(data);
	is_here_doc(data);
	tokenize(data);
	expand(data);
	remove_quotes(data);
	set_ex_(data);
	//debug_print_list(data);
}

t_data	*init_minishell(int argc, char **argv, char **envp, t_data *data)
{	
	if (argc != 1 || argv[1])
	{
		ft_putstr_fd("Minishell does not accept any arguments.", 2);
		exit(1);
	}
	data = ft_calloc(1, sizeof(t_data));;
	if (!data)
		print_error("Malloc error.", 1, data);
	(void)envp;
	get_env(data, envp);
	return (data);
}

void	exec_minishell(t_data *data)
{
	int		status;

	have_pipe(data);
	if (data->flag == 0) // if don't have pipes
	{
		if (!ft_strcmp(data->token->str, "exit"))
			get_exit(data, data->token, data->flag);
		else
			execution(data);
	}
	else
	{
		ft_signal_ignore();
		if (safe_fork(data) == 0)
			execution(data);
		waitpid(0, &status, 0);
		update_exit_code(status, data);
	}
}

void	loop_minishell(t_data *data)
{
	char	*buffer;

	buffer = NULL;
	while (1)
	{
		reset_fd_signals(data->fds[0], data->fds[1]);
		buffer = readline(C_CYAN"minishell: "END_COLOR);
		if (!valid_input(buffer, data))
			continue ;
		add_history(buffer);
		init_commands(buffer, data);
		if (!data->token)
			continue ;
		exec_minishell(data);
		free_token(data->token);
		unlink_here_doc_file();
	}
}

int main(int argc, char **argv, char **envp)
{
	t_data	*data;
	
	data = NULL;
	data = init_minishell(argc, argv, envp, data);
	data->fds[0] = dup(STDIN_FILENO);
	data->fds[1] = dup(1);
	data->exit_code = 0;
	loop_minishell(data);
}
