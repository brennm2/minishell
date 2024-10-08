/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 11:46:34 by bde-souz          #+#    #+#             */
/*   Updated: 2024/08/15 15:47:24 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	cd_error_invalid_option(t_data *data, int exit_flag)
{
	write(2, "minishell: cd: -", 16);
	write(2, &data->token->next->str[1], 1);
	write(2, ": invalid option\n", 17);
	ft_exit_flag(2, exit_flag, data);
}

void	cd_error_no_file(t_data *data, int exit_flag)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(data->token->next->str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	ft_exit_flag(1, exit_flag, data);
}

void	cd_error_invalid_file(t_data *data, t_token *token, int exit_flag)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(token->next->str, 2);
	ft_putstr_fd(": ", 2);
	perror("");
	ft_exit_flag(1, exit_flag, data);
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
			else if (!value)
			{
				temp_envp->invisible = 1;
				free(temp_envp->value);
				temp_envp->value = ft_strdup("\0");
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
