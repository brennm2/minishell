/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:12:51 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/07/11 11:54:21 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	free_tree(t_tree_root *cmd)
{
	int			argc;
	t_tree_exec	*execcmd;

	argc = 0;
	if (cmd->type == t_pipe)
	{
		free_tree(((t_tree_pipe *)(cmd))->left);
		free_tree(((t_tree_pipe *)(cmd))->right);
		free((t_tree_pipe *)(cmd));
	}
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

void	clean(t_data *data, int ex)
{
	(void)ex;
	if (!data)
		exit(1);
	free_env(data->envp);
	free_token(data->token);
	if (data->tree)
		free_tree(data->tree);
	if (data->home)
		free(data->home);
	free(data);
	rl_clear_history();
	exit(data->exit_code);
}