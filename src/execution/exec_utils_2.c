/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:14:55 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/08/07 19:23:08 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	exec_no_pipes(t_data *data, t_tree_exec *tree)
{
	int	status;
	int	pid;

	status = 0;
	pid = 0;
	ft_signal_def();
	pid = safe_fork(data);
	if (pid == 0)
		safe_execve(data, tree);
	ft_signal_ignore();
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		set_exit_code(WEXITSTATUS(status), data);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		if (WCOREDUMP(status))
			write(1, "Quit (core dumped)\n", 20);
		set_exit_code(WTERMSIG(status) + 128, data);
	}
}

void	cmd_execution(t_data *data, t_tree_exec *tree)
{
	if (tree->builtin_token && tree->builtin_token->type == builtin)
		get_builtin(data, tree->builtin_token, data->flag);
	else
	{
		if (data->flag == 0)
			exec_no_pipes(data, tree);
		else
			safe_execve(data, tree);
	}
}

void	test_sigint2(int signal)
{
	(void)signal;
}

void	right_exit(int status)
{
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			exit(130);
		if (WTERMSIG(status) == SIGQUIT)
			exit(131);
	}
}

void	pipe_execution(t_data *data, t_tree_root *tree)
{
	int	fd[2];
	int	status;
	int	pid_first;
	int	pid_sec;

	signal(SIGINT, test_sigint2);
	signal(SIGQUIT, test_sigint2);
	safe_pipe(fd, data);
	pid_first = safe_fork(data);
	if (pid_first == 0)
		pipe_child_execution(data, tree, fd, 1);
	pid_sec = safe_fork(data);
	if (pid_sec == 0)
		pipe_child_execution(data, tree, fd, 2);
	close(fd[0]);
	close(fd[1]);
	clean_withou_exit(data);
	waitpid(pid_first, &status, 0);
	waitpid(pid_sec, &status, 0);
	right_exit(status);
}
