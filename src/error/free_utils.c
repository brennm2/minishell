/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:12:51 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/08/12 12:42:01 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	free_tree(t_tree_root *cmd)
{
	int			argc;
	t_tree_exec	*execcmd;

	argc = 0;
	if (cmd->type == t_pipe)
		free_cmd_type(cmd);
	else if (cmd->type == t_redir)
	{
		free_tree(((t_tree_red *)(cmd))->tree);
		free((t_tree_red *)(cmd));
	}
	else if (cmd->type == t_exec)
	{
		execcmd = (t_tree_exec *)cmd;
		while (execcmd->argv[argc])
			free(execcmd->argv[argc++]);
		free(execcmd->argv);
		if (execcmd->cmd)
			free(execcmd->cmd);
		free(execcmd);
	}
}

void	unlink_here_doc_file(t_data *data)
{
	int		i;
	char	*file_name;

	if (data->hd == 0)
		return ;
	i = data->hd;
	while (i > 0)
	{
		file_name = creat_here_doc_file(i, false);
		if (access(file_name, F_OK) == -1)
		{
			free(file_name);
			return ;
		}
		unlink(file_name);
		free(file_name);
		i--;
	}
}

void	finished_exec(t_data *data, int exit_code)
{
	if (data->flag == 0)
	{
		free_token(data->token);
		if (data->tree)
			free_tree(data->tree);
		data->exit_code = exit_code;
		unlink_here_doc_file(data);
		loop_minishell(data);
	}
	else
		clean(data, exit_code);
}

void	clean_hd(t_data *data, int ex)
{
	if (!data)
		exit(1);
	free_env(data->envp);
	free_token(data->token);
	if (data->home)
		free(data->home);
	if (data->ex_)
		free(data->ex_);
	if (data->shlvl)
		free(data->shlvl);
	free(data);
	rl_clear_history();
	exit(ex);
}

void	clean(t_data *data, int ex)
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
	exit(ex);
}
