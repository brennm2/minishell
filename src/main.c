/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:20:02 by bde-souz          #+#    #+#             */
/*   Updated: 2024/08/06 18:45:34 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	init_commands(char *buffer, t_data *data)
{
	init_data(data, buffer);
	search_command(buffer, data);
	is_here_doc(data);
	tokenize(data);
	expand(data);
	remove_quotes(data);
	set_ex_(data);
}

t_data	*init_minishell(int argc, char **argv, char **envp, t_data *data)
{
	if (argc != 1 || argv[1])
	{
		ft_putstr_fd("Minishell does not accept any arguments.", 2);
		exit(1);
	}
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		print_error("Malloc error.", 1, data);
	(void)envp;
	change_shlvl(data, envp);
	get_env(data, envp);
	return (data);
}

void	sig_quit(int sig)
{
	(void)sig;
}

void	sig_int(int sig)
{
	(void)sig;
}

void	test_sigint(int signal)
{
	if (signal == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
	}
	if (signal == SIGQUIT)
	{
		write(STDERR_FILENO, "Quit (core dumped)\n", 20);
	}
}

void	exec_minishell(t_data *data)
{
	int	status;

	have_pipe(data);
	if (data->flag == 0)
		execution(data);
	else
	{
		if (safe_fork(data) == 0)
			execution(data);
		signal(SIGINT, test_sigint);
		signal(SIGQUIT, test_sigint);
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

void	catch_pid(t_data *data)
{
	int	pid;

	pid = safe_fork(data);
	if (pid == 0)
	{
		if (!data)
			exit(1);
		free_env(data->envp);
		if (data->home)
			free(data->home);
		if (data->shlvl)
			free(data->shlvl);
		free(data);
		exit(0);
	}
	else
	{
		wait(0);	
		data->pid = pid;
	}
}

void	change_shlvl(t_data *data, char **envp)
{
	int		i;
	int		lvl;
	char	*c_lvl;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "SHLVL=", 6))
		{
			lvl = ft_atoi(envp[i] + ft_strlen(envp[i]) - 1);
			lvl++;
			c_lvl = ft_itoa(lvl);
			data->shlvl = c_lvl;
			return ;
		}
	}
	data->shlvl = ft_strdup("2");
}

int main(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = NULL;
	data = init_minishell(argc, argv, envp, data);
	data->fds[0] = dup(STDIN_FILENO);
	data->fds[1] = dup(1);
	data->exit_code = 0;
	catch_pid(data);
	loop_minishell(data);
}

//echo "> >> < * ? [ ] | ; [ ] | | && ( ) & # $ <<"