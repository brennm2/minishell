/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cd_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:20:11 by bde-souz          #+#    #+#             */
/*   Updated: 2024/08/16 10:01:45 by bde-souz         ###   ########.fr       */
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
	(void)cwd;
	cd_change_last_oldpwd(data, 0);
	return (ft_exit_flag(0, exit_flag, data));
}

void	handle_tilde(t_data *data, t_token *token, int exit_flag)
{
	char	cwd[256];

	if (token->str[2] != '\0')
	{
		ft_putstr_fd("minishell: cd: --: invalid option\n", 2);
		return (ft_exit_flag(2, exit_flag, data));
	}
	else if (token->next && (token->next->type != is_pipe
			&& token->next->type != here_doc && token->next->type != append
			&& token->next->type != redout && token->next->type != redin))
	{
		ft_putstr_fd("minishell: cd: No such file or directory\n", 2);
		return (ft_exit_flag(1, exit_flag, data));
	}
	else
	{
		getcwd(cwd, sizeof(cwd));
		only_cd(data, cwd, exit_flag);
	}
}

bool	change_dir_update_env(t_data *data, char *old_cwd, char *new_pwd,
		int option)
{
	if (chdir(get_in_env(data->envp, "OLDPWD")) == 0)
	{
		data->envp = change_in_env(data->envp, old_cwd, "OLDPWD");
		if (option == 1)
		{
			ft_putstr_fd(new_pwd, 1);
			write(1, "\n", 1);
		}
		data->envp = change_in_env(data->envp, new_pwd, "PWD");
		free(new_pwd);
		return (false);
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(get_in_env(data->envp, "OLDPWD"));
		free(new_pwd);
		return (true);
	}
}
