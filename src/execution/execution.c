/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:28:34 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/06/26 20:53:18 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/* void	get_builtin_ex(t_tree_exec *cmd)
{
	if(cmd->token->builtin == echo && !ft_strcmp(cmd->token->str, "echo"))
		get_echo(data->token->next, data); //Entra com o proximo <NODE>
	else if (cmd->token->builtin == pwd && !ft_strcmp(cmd->token->str, "pwd"))
		get_pwd(data->token);
	else if (cmd->token->builtin == cd && !ft_strcmp(cmd->token->str, "cd"))
		get_cd(data);
	else if (cmd->token->builtin == env && !ft_strcmp(cmd->token->str, "env"))
		get_builtin_env(data);
	else if (cmd->token->builtin == n_exit
		&& !ft_strcmp(cmd->token->str, "exit"))
		get_exit(data);
	else if(cmd->token->builtin == export
		&& !ft_strcmp(cmd->token->str, "export"))
		get_export(data);
	else
		command_not_found(data->token); //#TODO Verificar se isso pode ficar aqui

} */

void	cmd_execution(t_data *data, t_tree_cmd *tree)
{
	int status;
	int pid;
	
	status = 0;
	pid = 0;
	if (tree->token->type == builtin)
		get_builtin(); // TODO
	else
	{
		pid = safe_fork(data);
		if (pid == 0)
			safe_execve(data, tree);
	}
}

void	exec_execution(t_data *data, t_tree_cmd *tree)
{
	t_tree_exec	*ecmd;

	ecmd = (t_tree_exec *)tree;
	if (ecmd->argv[0] && !ft_strcmp(ecmd->argv[0], "exit"))
		G_EXIT_CODE = 0;
	else
		cmd_execution(data, ecmd);
	exit(G_EXIT_CODE);	
}

void	redir_execution(t_data *data, t_tree_cmd *tree)
{
	t_tree_red *rcmd;

	rcmd = (t_tree_red *)tree;
	close(rcmd->fd);
	if (open(rcmd->file, rcmd->mode, rcmd->perm) < 0)
	{
		G_EXIT_CODE = 1;
		write(2, "minishell: ", 12);
		perror(rcmd->file);
		exit(G_EXIT_CODE);
	}
	executing_tree(data, rcmd->token);
}

void	pipe_execution(t_data *data, t_tree_cmd *tree)
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
	exit(G_EXIT_CODE);
}

void	executing_tree(t_data *data, t_tree_cmd *tree)
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
	build_tree(data);
	executing_tree(data, data->tree);
}