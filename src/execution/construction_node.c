/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construction_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:29:16 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/07/01 12:45:02 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	count_args(t_data *data, t_token *token)
{
	t_token	*aux;
	int		nbr;

	nbr = 0;
	aux = token;
	while (aux)
	{
		if (aux->type == command || aux->type == builtin || aux->type == string)
			nbr++;
		else if (aux->type == is_pipe)
			break ;
		aux = aux->next;
	}
	return (nbr);
}

t_tree_cmd	*const_exec(t_data *data, t_token *token)
{
	t_tree_exec	*exec_cmd;
	int			args;
	
	(void)data;
	exec_cmd = ft_calloc(1, sizeof(t_tree_exec));
	if (!exec_cmd)
		exit(1);
	ft_memset(exec_cmd, 0, sizeof(t_tree_exec));
	exec_cmd->type = t_exec;
	exec_cmd->token = token;
	args = count_args(data, token);
	exec_cmd->argv = ft_calloc(args, sizeof(char *));
	if (!exec_cmd->argv)
		clean(data, 1);
	exec_cmd->cmd = NULL;
	return ((t_tree_cmd *)exec_cmd);
}

t_tree_cmd	*get_red(t_tree_cmd *red_cmd)
{
	t_tree_red	*redir;
	
	while (red_cmd->type == t_redir)
	{
		redir = (t_tree_red *)red_cmd;
		if (redir->tree->type == t_exec)
			break ;
		else
			red_cmd = redir->tree;
	}
	return (red_cmd);
}

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
		red_cmd->tree = ((t_tree_red *)old)->tree;
		((t_tree_red *)(old))->tree = (t_tree_cmd *)red_cmd;
		return (scmd);
	}
	return ((t_tree_cmd *)red_cmd);
}

t_tree_cmd	*const_pipe(t_data *data, t_tree_cmd *left, t_tree_cmd *right)
{
	t_tree_pipe	*pipe_cmd;
	
	pipe_cmd = ft_calloc(1, sizeof(t_tree_pipe));
	if (!pipe_cmd)
		clean(data, 1);
	ft_memset(pipe_cmd, 0, sizeof(t_tree_pipe));
	pipe_cmd->type = t_pipe;
	pipe_cmd->left = left;
	pipe_cmd->right = right;
	return ((t_tree_cmd *)pipe_cmd);
}