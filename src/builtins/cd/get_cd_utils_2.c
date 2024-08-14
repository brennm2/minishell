/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cd_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:20:11 by bde-souz          #+#    #+#             */
/*   Updated: 2024/08/14 11:12:23 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	handle_plus_option(t_data *data, char *cwd, int exit_flag)
{
	chdir(cwd);
	data->envp = change_in_env(data->envp, cwd, "OLDPWD");
	data->envp = change_in_env(data->envp, cwd, "PWD");
	return (ft_exit_flag(0, exit_flag, data));
}

void	handle_minus_option(t_data *data, char *cwd, int exit_flag)
{
	cd_change_last_oldpwd(data, 0);
	getcwd(cwd, sizeof(cwd));
	data->envp = change_in_env(data->envp, cwd, "PWD");
	return (ft_exit_flag(0, exit_flag, data));
}

void	handle_tilde(t_data *data, t_token *token, int exit_flag, char *cwd)
{
	(void)token;
	if (get_in_env(data->envp, "OLDPWD") == NULL)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		ft_exit_flag(1, exit_flag, data);
		return ;
	}
	cd_change_last_oldpwd(data, 0);
	chdir(get_in_env(data->envp, "HOME"));
	getcwd(cwd, sizeof(cwd));
	data->envp = change_in_env(data->envp, cwd, "PWD");
	ft_exit_flag(0, exit_flag, data);
}

bool	change_dir_update_env(t_data *data, char *old_cwd, char *old_cwd_char,
		int option)
{
	if (chdir(old_cwd_char) != -1)
	{
		data->envp = change_in_env(data->envp, old_cwd, "OLDPWD");
		if (option == 1)
		{
			ft_putstr_fd(old_cwd_char, 1);
			write(1, "\n", 1);
		}
		free(old_cwd_char);
		return (false);
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(get_in_env(data->envp, "OLDPWD"));
		free(old_cwd_char);
		return (true);
	}
}
