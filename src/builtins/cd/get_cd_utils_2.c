/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cd_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:20:11 by bde-souz          #+#    #+#             */
/*   Updated: 2024/08/06 13:29:00 by bde-souz         ###   ########.fr       */
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