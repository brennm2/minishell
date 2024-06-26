/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:29:16 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/06/26 15:57:42 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_tree_cmd	*const_redir(t_tree_cmd *scmd, char *file, int mode, int fd)
{
	t_tree_red	*red_cmd;
	t_tree_cmd	*old;
	
	red_cmd = ft_calloc(1, sizeof(t_tree_red));
	red_cmd->type = t_redir;
	red_cmd->tree = scmd;
	red_cmd->file = file;
	red_cmd->mode = mode;
	red_cmd->fd = fd;
	if (fd == 0)
		red_cmd->perm = 0444;
	else
		red_cmd->perm = 0644;
	red_cmd->token = scmd->token;
	if (scmd->type != t_exec)
	{
		old = get_red((t_tree_cmd *)red_cmd);
		red_cmd->
	}
}

t_tree_cmd	*const_pipe(t_data *data, t_tree_cmd *left, t_tree_cmd *right)
{
	t_tree_pipe	*pipe_cmd;
	
	pipe_cmd = ft_calloc(1, sizeof(t_tree_pipe));
	if (!pipe_cmd)
		quick_exit(1);
	ft_memset(pipe_cmd, 0, sizeof(t_tree_pipe));
	pipe_cmd->type = t_pipe;
	pipe_cmd->left = left;
	pipe_cmd->right = right;
	return ((t_tree_cmd *)pipe_cmd);
}