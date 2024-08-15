/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:48:41 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/08/10 11:34:31 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	set_exit_code(int code, t_data *data)
{
	data->exit_code = code;
}

void	update_exit_code(int status, t_data *data)
{
	if (WIFEXITED(status))
	{
		set_exit_code(WEXITSTATUS(status), data);
	}
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			write(1, "\n", 1);
			set_exit_code(WTERMSIG(status) + 128, data);
		}
		if (WCOREDUMP(status))
		{
			write(1, "Quit (core dumped)\n", 20);
			set_exit_code(WTERMSIG(status) + 128, data);
		}
	}
}

void	catch_pid(t_data *data)
{
	int	pid;

	pid = safe_fork(data);
	if (pid == 0)
	{
		if (!data)
			exit(1);
		free_env(data->envp);
		if (data->home)
			free(data->home);
		if (data->shlvl)
			free(data->shlvl);
		free(data);
		exit(0);
	}
	else
	{
		wait(0);
		data->pid = pid;
	}
}

void	change_shlvl(t_data *data, char **envp)
{
	int		i;
	int		lvl;
	char	*c_lvl;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "SHLVL=", 6))
		{
			lvl = ft_atoi(envp[i] + ft_strlen(envp[i]) - 1);
			lvl++;
			c_lvl = ft_itoa(lvl);
			data->shlvl = c_lvl;
			return ;
		}
	}
	data->shlvl = ft_strdup("1");
}
