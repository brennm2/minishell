/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 11:46:34 by bde-souz          #+#    #+#             */
/*   Updated: 2024/07/04 12:01:44 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	cd_error_invalid_option(t_data *data)
{
	write(2, "minishell: cd: -", 16);
	write(2, &data->token->next->str[1], 1);
	write(2, ": invalid option\n", 17);
	print_error(NULL, 2);
}

void	cd_error_invalid_file(t_data *data)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(data->token->next->str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	print_error(NULL, 1);
}

t_envp	*change_in_env(t_envp *envp, char *value, char *key)
{
	t_envp	*temp_envp;

	temp_envp = envp;
	while (temp_envp)
	{
		if (ft_strcmp(temp_envp->key, key) == 0)
		{
			if (value)
			{
				temp_envp->invisible = 0;
				free(temp_envp->value);
				temp_envp->value = ft_strdup(value);
			}
			return (envp);
		}
		temp_envp = temp_envp->next;
	}
	return (envp);
}

char	*get_in_env(t_envp *envp, char *key)
{
	t_envp	*temp_envp;

	temp_envp = envp;
	while (temp_envp)
	{
		if (ft_strcmp(temp_envp->key, key) == 0)
			return (temp_envp->value);
		temp_envp = temp_envp->next;
	}
	return (NULL);
}
