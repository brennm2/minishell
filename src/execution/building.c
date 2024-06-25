/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   building.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:14:11 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/06/25 21:23:52 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_tree_cmd	*building_redir(t_data *data, t_tree_cmd *tree_cmd)
{
	t_token	*token;
	int		r_type;

	token = tree_cmd->token;
	r_type = token->type;
	if (r_type == redin || r_type == here_doc)
		tree_cmd = const_redir(tree_cmd, token, O_RDONLY, 0);
	else if (r_type == redout)
		tree_cmd = const_redir(tree_cmd, token, O_WRONLY | O_CREAT | O_TRUNC, 1);
	else if (r_type == append)
		tree_cmd = const_redir(tree_cmd, token, O_WRONLY | O_CREAT | O_APPEND, 1);
	if (!tree_cmd)
		get_exit(data);
	return (tree_cmd);
}

t_tree_cmd	*building_exec(t_data *data, t_token *token)
{
	t_tree_cmd	*tree_cmd;
	t_token		*aux;
	t_tree_exec	*exec_cmd;
	
	tree_cmd = const_exec(data, token);
	exec_cmd = (t_tree_cmd *)tree_cmd;
	aux = tree_cmd->token;
	while (aux)
	{
		tree_cmd->token = aux;
		if (aux->type == string || aux->type == command || aux->type == builtin)
			get_exec(data, exec_cmd, aux);
		else if (aux->type == redin || aux->type == redout || aux->type == append || aux->type == here_doc)
			tree_cmd = building_redir(data, tree_cmd);
		else if (aux->type == is_pipe)
			break ;
		aux = aux->next;			
	}
	return (tree_cmd);
}

t_tree_cmd	*building_pipe(t_data *data, t_token *token)
{
	t_tree_cmd	*tree_cmd;

	tree_cmd = building_exec(data, token);
	token = tree_cmd->token;
	if (tree_cmd && token && token->type == is_pipe)
	{
		token = token->next;
		tree_cmd = const_pipe(data, tree_cmd, building_pipe(data, token));
	}
}

void	building_tree(t_data *data)
{
	data->tree = building_pipe(data, data->token);
}