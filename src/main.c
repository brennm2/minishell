/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:20:02 by bde-souz          #+#    #+#             */
/*   Updated: 2024/07/19 13:39:26 by nsouza-o         ###   ########.fr       */
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

void	set_ex_(t_data *data)
{
	t_token	*aux;

	aux = data->token;
	while (aux)
	{
		if (data->ex_)
			free(data->ex_);
		data->ex_ = ft_strdup(aux->str);
		if (aux->next && is_red_or_pipe(aux->next))
			break ;
		aux = aux->next;
	}
}

bool	is_red_bool(t_token *token)
{
	if (token->type == redin)
		return (true);
	else if (token->type == redout)
		return (true);
	else if (token->type == append)
		return (true);
	return (false);
}

void	update_token(t_data *data)
{
	t_token	*token_aux;
	t_token *dead;

	token_aux = data->token;
	if (token_aux->str[0] == '\0' && !is_red_bool(token_aux))
	{
		data->token = token_aux->next;
		free_token_redir(token_aux);
		if (data->token && data->token->type == string)
			which_command(data->token);
		return ;
	}
	while (token_aux)
	{
		if (token_aux->builtin != cd && token_aux->next && token_aux->next->str[0] == '\0' && token_aux->next->type == string)
		{
			dead = token_aux->next;
			token_aux->next = token_aux->next->next;
			free_token_redir(dead);
		}
		token_aux = token_aux->next;
	}
}

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
	update_token(data);
	set_ex_(data);
	//debug_print_list(data);
}


t_data	*init_minishell(int argc, char **argv, char ** envp, t_data *data)
{	
	if (argc != 1 || argv[1])
	{
		ft_putstr_fd("Minishell does not accept any arguments.", 2);
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
	else if (WIFSIGNALED(status))
		set_exit_code(WTERMSIG(status), data);
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

void	reset_fd_signals(int fd1, int fd2)
{
	ft_catch_signal(MAIN);
	dup2(fd1, STDIN_FILENO);
	dup2(fd2, STDOUT_FILENO);
}

void	have_pipe(t_data *data)
{
	t_token *token_aux;

	token_aux = data->token;
	while (token_aux)
	{
		if (token_aux->type == is_pipe)
		{
			data->flag = 1;
			return ;
		}
		token_aux = token_aux->next;
	}
	data->flag = 0;
}

void	loop_minishell(t_data *data)
{
	char	*buffer;
	int		status;

	buffer = NULL;
	data->exit_code = 0;
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

