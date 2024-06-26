/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   building.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:14:11 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/06/26 20:53:05 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_tree_cmd	*build_redir(t_data *data, t_tree_cmd *tree_cmd)
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
		exit(1);
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
		exit(1);
	if (i == 0)
		cmd->cmd = get_path(data, cmd->argv[0]);
}

t_tree_cmd	*build_exec(t_data *data, t_token *token)
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
			get_exec(data, exec_cmd, aux->str);
		else if (aux->type == redin || aux->type == redout || aux->type == append || aux->type == here_doc)
			tree_cmd = build_redir(data, tree_cmd);
		else if (aux->type == is_pipe)
			break ;
		aux = aux->next;			
	}
	return (tree_cmd);
}

t_tree_cmd	*build_pipe(t_data *data, t_token *token)
{
	t_tree_cmd	*tree_cmd;

	tree_cmd = build_exec(data, token);
	token = tree_cmd->token;
	if (tree_cmd && token && token->type == is_pipe)
	{
		token = token->next;
		tree_cmd = const_pipe(data, tree_cmd, build_pipe(data, token));
	}
}

void	build_tree(t_data *data)
{
	data->tree = build_pipe(data, data->token);
}