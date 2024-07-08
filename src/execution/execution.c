/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:28:34 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/07/08 19:28:26 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	cmd_execution(t_data *data, t_tree_exec *tree)
{
	int status;
	int pid;
	
	status = 0;
	pid = 0;
	if (tree->token->type == builtin)
		printf("builting\n");
	else
	{
		pid = safe_fork(data);
		if (pid == 0)
			safe_execve(data, tree);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			set_exit_code(WEXITSTATUS(status));
	}
}

void	exec_execution(t_data *data, t_tree_root *tree)
{
	t_tree_exec	*ecmd;

	ecmd = (t_tree_exec *)tree;
	if (ecmd->argv[0])
		cmd_execution(data, ecmd);
	clean(data, G_EXIT_CODE);	
}

void	redir_execution(t_data *data, t_tree_root *tree)
{
	t_tree_red *rcmd;

	rcmd = (t_tree_red *)tree;
	close(rcmd->fd);
	if (open(rcmd->file, rcmd->mode, rcmd->perm) < 0)
	{
		G_EXIT_CODE = 1;
		write(2, "minishell: ", 12);
		perror(rcmd->file);
		clean(data, G_EXIT_CODE);
	}
	executing_tree(data, rcmd->tree);
}

void	pipe_execution(t_data *data, t_tree_root *tree)
{
	int	fd[2];
	int status;
	int	pid1;
	int pid2;
	
	safe_pipe(fd, data);
	pid1 = safe_fork(data);
	if (pid1 == 0)
		pipe_child_execution(data, tree, fd, 1);
	pid2 = safe_fork(data);
	if (pid2 == 0)
		pipe_child_execution(data, tree, fd, 2);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		G_EXIT_CODE = WEXITSTATUS(status);
	clean(data, G_EXIT_CODE);
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