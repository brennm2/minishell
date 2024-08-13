/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:28:34 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/08/12 13:37:53 by nsouza-o         ###   ########.fr       */
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
	t_tree_red	*rcmd;

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
		else
		{
			write(2, "minishell: ", 12);
			perror(rcmd->file);
		}
		finished_exec(data, 1);
	}
	executing_tree(data, rcmd->tree);
}

void	clean_withou_exit(t_data *data)
{
	if (!data)
		exit(1);
	free_env(data->envp);
	free_token(data->token);
	if (data->tree)
		free_tree(data->tree);
	if (data->home)
		free(data->home);
	if (data->ex_)
		free(data->ex_);
	if (data->shlvl)
		free(data->shlvl);
	free(data);
	rl_clear_history();
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
