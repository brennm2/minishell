/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:28:34 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/07/24 15:27:42 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	exec_execution(t_data *data, t_tree_root *tree)
{
	t_tree_exec	*ecmd;

	ecmd = (t_tree_exec *)tree;
	if (ecmd->argv[0] && ft_strcmp(ecmd->argv[0], "\0"))
		cmd_execution(data, ecmd);
	finished_exec(data, data->exit_code);
}

void	redir_execution(t_data *data, t_tree_root *tree)
{
	t_tree_red *rcmd;

	rcmd = (t_tree_red *)tree;
	close(rcmd->fd);
	if (open(rcmd->file, rcmd->mode, rcmd->perm) < 0)
	{
		if (!ft_strcmp(rcmd->file, "\0") && rcmd->exp)
		{
			write(2, "minishell: ", 12);
			ft_putstr_fd(rcmd->exp, 2);
			ft_putstr_fd(": ambiguous redirect\n", 2);
		}
		else if (!access(rcmd->file, F_OK))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(rcmd->exp, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		else
			perror(rcmd->file);
		finished_exec(data, 1);
	}
	executing_tree(data, rcmd->tree);
}

void	pipe_execution(t_data *data, t_tree_root *tree)
{
	int	fd[2];
	int status;
	int	pid_first;
	int pid_sec;
	
	safe_pipe(fd, data);
	pid_first = safe_fork(data);
	if (pid_first == 0)
		pipe_child_execution(data, tree, fd, 1);
	pid_sec = safe_fork(data);
	if (pid_sec == 0)
		pipe_child_execution(data, tree, fd, 2);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid_first, &status, 0);
	waitpid(pid_sec, &status, 0);
	if (WIFEXITED(status))
		data->exit_code = WEXITSTATUS(status);
	finished_exec(data, data->exit_code);
}

void	executing_tree(t_data *data, t_tree_root *tree)
{
	if (tree->type == t_exec)
		exec_execution(data, tree);
	else if (tree->type == t_redir)
		redir_execution(data, tree);
	else if (tree->type == t_pipe)
		pipe_execution(data, tree);
}

void	execution(t_data *data)
{
	data->tree = pipe_struct(data, data->token);
	executing_tree(data, data->tree);
}