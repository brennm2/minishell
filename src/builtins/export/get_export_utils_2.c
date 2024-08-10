/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_export_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:32:23 by bde-souz          #+#    #+#             */
/*   Updated: 2024/08/09 11:52:22 by nsouza-o         ###   ########.fr       */
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
	int	flag;

	i = 0;
	flag = 0;
	if (!ft_isalpha(key[0]) && ft_isdigit(key[0]))
		return (false);
	while (key[i])
	{
		if (key[i] == '=' && flag == 0)
			flag++;
		if (!ft_isalnum(key[i]) && key[i] != '_' && key[i] != '='
			&& key[i] != ' ' && flag == 0)
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

void	swap_nodes(t_envp *current_node, t_envp *next_node)
{
	char	*key;
	char	*value;
	int		invisible;

	key = current_node->key;
	value = current_node->value;
	invisible = current_node->invisible;
	current_node->key = next_node->key;
	current_node->value = next_node->value;
	current_node->invisible = next_node->invisible;
	next_node->key = key;
	next_node->value = value;
	next_node->invisible = invisible;
}

t_envp	*organize_envp_list(t_envp *duplicate_env)
{
	t_envp	*current_node;
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
