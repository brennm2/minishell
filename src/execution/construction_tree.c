/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construction_tree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:14:11 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/07/10 15:44:12 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_tree_root	*redir_struct(t_data *data, t_tree_root *tree_cmd)
{
	t_token	*token;
	int		r_type;

	token = tree_cmd->token;
	r_type = token->type;
	if (r_type == redin || r_type == here_doc)
		tree_cmd = const_redir(tree_cmd, token->str, O_RDONLY, STDIN_FILENO);
	else if (r_type == redout)
		tree_cmd = const_redir(tree_cmd, token->str, O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO);
	else if (r_type == append)
		tree_cmd = const_redir(tree_cmd, token->str, O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO);
	if (!tree_cmd)
		clean(data, 1);
	return (tree_cmd);
}

void	get_exec(t_data *data, t_tree_exec *cmd, char *arg)
{
	int	i;

	i = 0;
	while (cmd->argv[i])
		i++;
	cmd->argv[i] = ft_strdup(arg);
	if (!cmd->argv[i])
		clean(data, 1);
	if (i == 0)
		cmd->cmd = get_path(data, cmd->argv[0]);
}

t_tree_root	*exec_struct(t_data *data, t_token *token)
{
	t_tree_root	*tree_cmd;
	//t_token		*cont;
	t_token		*temp;
	t_tree_exec	*exec_cmd;
	
	tree_cmd = const_exec(data, token);
	exec_cmd = (t_tree_exec *)tree_cmd;
	temp = tree_cmd->token;
	while (temp)
	{
		//cont = temp->content;
		tree_cmd->token = temp;
		if (temp->type == string || temp->type == command || temp->type == builtin)
			get_exec(data, exec_cmd, temp->str);
		else if (temp->type == redin || temp->type == redout || temp->type == append || temp->type == here_doc)
			tree_cmd = redir_struct(data, tree_cmd);
		else if (temp->type == is_pipe)
			break ;
		temp = temp->next;			
	}
	return (tree_cmd);
}

t_tree_root	*pipe_struct(t_data *data, t_token *token)
{
	t_tree_root	*tree_cmd;

	tree_cmd = exec_struct(data, token);
	token = tree_cmd->token;
	if (tree_cmd && token && token->type == is_pipe)
	{
		token = token->next;
		tree_cmd = const_pipe(data, tree_cmd, pipe_struct(data, token));
	}
	return (tree_cmd);
}
