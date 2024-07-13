/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:12:51 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/07/13 12:03:01 by nsouza-o         ###   ########.fr       */
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

void	unlink_here_doc_file(void)
{
	int	i;
	char	*file_name;
	
	i = -1;
	while (1)
	{
		file_name = creat_here_doc_file(++i, 0);
		if (access(file_name, F_OK) == -1)
			break ;
		unlink(file_name);
		free(file_name);
	}
	free(file_name);
}

void	clean(t_data *data, int ex)
{
	//(void)ex;
	if (!data)
		exit(1);
	free_env(data->envp);
	free_token(data->token);
	//unlink_here_doc_file();
	/* if (data->fd_here_doc)
		unlink("here_doc_file"); */
	if (data->tree)
		free_tree(data->tree);
	if (data->home)
		free(data->home);
	free(data);
	rl_clear_history();
	exit(ex);
}