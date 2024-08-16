/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:50:20 by bde-souz          #+#    #+#             */
/*   Updated: 2024/08/15 15:21:03 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

bool	cd_change_last_oldpwd(t_data *data, int option)
{
	char	old_cwd[256];
	char	*old_cwd_char;

	getcwd(old_cwd, sizeof(old_cwd));
	if (get_in_env(data->envp, "OLDPWD") == NULL)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (true);
	}
	else
		old_cwd_char = ft_strdup(get_in_env(data->envp, "OLDPWD"));
	return (change_dir_update_env(data, old_cwd, old_cwd_char, option));
}

void	cd_options_tilde(t_data *data, int exit_flag)
{
	char	cwd[256];

	if (data->token->next->str[0] == '-' && data->token->next->str[1] == '+')
		return (cd_error_invalid_option(data, exit_flag));
	getcwd(cwd, sizeof(cwd));
	if (data->token->next->str[1] == '+')
	{
		if (get_in_env(data->envp, "PWD") == NULL)
		{
			ft_putstr_fd("minishell: cd: ~+: No such file or directory\n", 2);
			return (ft_exit_flag(1, exit_flag, data));
		}
		handle_plus_option(data, cwd, exit_flag);
	}
	else if (data->token->next->str[1] == '-')
	{
		if (get_in_env(data->envp, "OLDPWD") == NULL)
		{
			ft_putstr_fd("minishell: cd: ~-: No such file or directory\n", 2);
			return (ft_exit_flag(1, exit_flag, data));
		}
		handle_minus_option(data, cwd, exit_flag);
	}
}

void	cd_options(t_data *data, t_token *token, int exit_flag)
{
	char	cwd[256];

	if (token->next->str[1] && (token->next->str[1] != '-'
			&& token->next->str[1] != '+'))
	{
		if (token->next->str[0] == '~' && token->next->str[1])
			return (cd_error_no_file(data, exit_flag));
		return (cd_error_invalid_option(data, exit_flag));
	}
	else if ((token->next->str[0] == '-' && token->next->str[1] == '-'))
		return (handle_tilde(data, token->next, exit_flag));
	else if (token->next->str[1] == '+' || (token->next->str[1] == '-'))
		return (cd_options_tilde(data, exit_flag));
	if (cd_change_last_oldpwd(data, 1) == true)
		return (ft_exit_flag(1, exit_flag, data));
	getcwd(cwd, sizeof(cwd));
	data->envp = change_in_env(data->envp, cwd, "PWD");
	return (ft_exit_flag(0, exit_flag, data));
}

void	only_cd(t_data *data, char *old_cwd, int exit_flag)
{
	if (get_in_env(data->envp, "HOME") == NULL)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (ft_exit_flag(1, exit_flag, data));
	}
	else
	{
		chdir(get_in_env(data->envp, "HOME"));
		change_in_env(data->envp, old_cwd, "OLDPWD");
		change_in_env(data->envp, get_in_env(data->envp, "HOME"), "PWD");
		return (ft_exit_flag(0, exit_flag, data));
	}
}

void	get_cd(t_data *data, t_token *token, int exit_flag)
{
	char	cwd[256];
	char	*old_cwd;

	old_cwd = get_in_env(data->envp, "PWD");
	if (token->next && token->next->type == string)
	{
		if (token->next->str[0] == '\0')
			return (ft_exit_flag(0, exit_flag, data));
		else if ((token->next->str[0] == '-' || token->next->str[0] == '~'))
			return (cd_options(data, token, exit_flag));
		else if (token->next && token->next->next
			&& token->next->next->type == string)
			return (p_error_flag(ERROR_CD_MANY_ARGUMENT, 1, data, exit_flag));
		else if (!chdir(token->next->str))
		{
			getcwd(cwd, sizeof(cwd));
			data->envp = change_in_env(data->envp, old_cwd, "OLDPWD");
			data->envp = change_in_env(data->envp, cwd, "PWD");
			return (ft_exit_flag(0, exit_flag, data));
		}
		else if (token->next && token->next->type == string)
			return (cd_error_invalid_file(data, token, exit_flag));
	}
	else
		only_cd(data, old_cwd, exit_flag);
}
