/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_export_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:32:23 by bde-souz          #+#    #+#             */
/*   Updated: 2024/07/03 16:37:32 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

t_envp	*duplicate_next_node(t_envp *duplicate_env, t_envp *temp_env)
{
	if (temp_env->next)
	{
		duplicate_env->next = ft_calloc(1, sizeof(t_envp));
		duplicate_env = duplicate_env->next;
	}
	else
		duplicate_env->next = NULL;
	return (duplicate_env);
}

bool	is_invalid_token(char *key)
{
	int	i;

	i = 0;
	if (!ft_isalpha(key[0]) && ft_isdigit(key[0]))
		return (false);
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_' && key[i] != '=' && key[i] != ' ')
			return (false);
		if (key[i] && key[i + 1] == ' ')
			return (false);
		i++;
	}
	return (true);
}

char	*find_key(char *str)
{
	int		i;
	char	*temp_str;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	temp_str = ft_calloc(i + 1, sizeof(char *));
	ft_strlcpy(temp_str, str, i + 1);
	return (temp_str);
}

void swap_nodes(t_envp *node1, t_envp *node2)
{
	char	*key = node1->key;
	char	*value = node1->value;
	int	invisible = node1->invisible;

    node1->key = node2->key;
    node1->value = node2->value;
    node1->invisible = node2->invisible;

    node2->key = key;
    node2->value = value;
    node2->invisible = invisible;
}

t_envp	*organize_envp_list(t_envp *duplicate_env)
{
    t_envp	*current_node;// = duplicate_env;
    t_envp	*next_node;

	current_node = duplicate_env;
    while (current_node && current_node->next)
    {
        next_node = current_node->next;
        while (next_node)
        {
            if (ft_strcmp(current_node->key, next_node->key) > 0)
                swap_nodes(current_node, next_node);
            next_node = next_node->next;
        }
        current_node = current_node->next;
    }
    return (duplicate_env);
}

// t_envp	*organize_envp_list(t_envp *duplicate_env)
// {
// 	t_envp	*current_node;
// 	t_envp	*next_node;
// 	char	*key;
// 	char	*value;
// 	int		invisible;

// 	current_node = duplicate_env;
// 	while (current_node->next)
// 	{
// 		next_node = current_node->next;
// 		while (next_node)
// 		{
// 			if (ft_strcmp(current_node->key, next_node->key) > 0)
// 			{
// 				key = current_node->key;
// 				value = current_node->value;
// 				invisible = current_node->invisible;
// 				current_node->key = next_node->key;
// 				current_node->value = next_node->value;
// 				current_node->invisible = next_node->invisible;
// 				next_node->key = key;
// 				next_node->value = value;
// 				next_node->invisible = invisible;
// 			}
// 			next_node = next_node->next;
// 		}
// 		current_node = current_node->next;
// 	}
// 	return (duplicate_env);
// }