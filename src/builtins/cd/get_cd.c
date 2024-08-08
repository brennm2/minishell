/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:50:20 by bde-souz          #+#    #+#             */
/*   Updated: 2024/08/08 16:58:45 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

bool	cd_change_last_oldpwd(t_data *data, int option)
{
	char	old_cwd[256];
	char	*old_cwd_char;

	getcwd(old_cwd, sizeof(old_cwd));
	old_cwd_char = ft_strdup(get_in_env(data->envp, "OLDPWD")); //WHAT????
	if (chdir(old_cwd_char) != -1)
	{
		data->envp = change_in_env(data->envp, old_cwd, "OLDPWD");
		if (option == 1)
		{
			ft_putstr_fd(old_cwd_char, 1);
			write(1, "\n", 1);
		}
		free (old_cwd_char);
		return (false);
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(get_in_env(data->envp, "OLDPWD"));
		free (old_cwd_char);
		return (true);
	}
}

void	cd_options_tilde(t_data *data, int exit_flag)
{
	char	cwd[256];

	if (data->token->next->str[0] == '-' && data->token->next->str[1] == '+')
		return (cd_error_invalid_option(data, exit_flag));
	getcwd(cwd, sizeof(cwd));
	if (data->token->next->str[1] == '+') //Vai para o pwd atual e mudar o pwd antigo para o pwd atual
	{
		if (get_in_env(data->envp, "PWD") == NULL)
		{
			ft_putstr_fd("minishell: cd: ~+: No such file or directory\n", 2);
			return (ft_exit_flag(1, exit_flag, data));
		}
		handle_plus_option(data, cwd, exit_flag);
	}
	else if (data->token->next->str[1] == '-') // Vai para o OLDPWD e mudar o OLDPWD para o atual PWD
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
		if (token->next->str[0] == '~' && token->next->str[1]) //Se for "cd ~algumacoisa"
			return (cd_error_no_file(data, exit_flag));
		return (cd_error_invalid_option(data, exit_flag)); //Se for "cd -algumacoisa";
	}
	else if ((token->next->str[0] == '-' && token->next->str[1] == '-')
		|| (token->next->str[0] == '~' && token->next->str[1] == '\0')) // se for "cd --" ou "cd ~"
	{
		cd_change_last_oldpwd(data, 0);
		chdir(get_in_env(data->envp, "HOME"));
		getcwd(cwd, sizeof(cwd));
		data->envp = change_in_env(data->envp, cwd, "PWD");
		return (ft_exit_flag(0, exit_flag, data));
	}
	else if (token->next->str[1] == '+' || (token->next->str[1] == '-')) // Se for "CD ~-" OU "CD ~+"
		return (cd_options_tilde(data, exit_flag));
	if (cd_change_last_oldpwd(data, 1) == true) // Se nao entrar em nada, entao "cd -", se for true retorna com exit_code 1
		return (ft_exit_flag(1, exit_flag, data));
	getcwd(cwd, sizeof(cwd)); //Pega o PWD atual
	data->envp = change_in_env(data->envp, cwd, "PWD"); // Muda no env->PWD
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
	if (token->next && token->next->type == string) //se for "cd ..."
	{
		if (token->next->str[0] == '\0')
			return (ft_exit_flag(0, exit_flag, data));
		else if ((token->next->str[0] == '-' || token->next->str[0] == '~')) //se for "cd -" OU "cd ~-" OU "cd ~+" OU "cd ~"
			return (cd_options(data, token, exit_flag));
		else if (token->next && token->next->next
			&& token->next->next->type == string) // Se for "cd a b"
			return (p_error_flag(ERROR_CD_MANY_ARGUMENT, 1, data, exit_flag));
		else if (!chdir(token->next->str)) //Executar o comando normal "cd src/", caso nao encontre, nao entre
		{
			getcwd(cwd, sizeof(cwd));
			data->envp = change_in_env(data->envp, old_cwd, "OLDPWD");
			data->envp = change_in_env(data->envp, cwd, "PWD");
			return (ft_exit_flag(0, exit_flag, data));
		}
		else if (token->next && token->next->type == string)
			return (cd_error_invalid_file(data, token, exit_flag)); // Se "cd algumacoisa" (nao for um diretorio valido)
	}
	else // se for somente "cd"
		only_cd(data, old_cwd, exit_flag);
}
