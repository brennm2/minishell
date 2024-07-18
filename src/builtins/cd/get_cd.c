/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:50:20 by bde-souz          #+#    #+#             */
/*   Updated: 2024/07/18 19:03:14 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	cd_change_last_oldpwd(t_data *data, int option) //
{
	char	old_cwd[256];
	char	*old_cwd_char;

	getcwd(old_cwd, sizeof(old_cwd));
	old_cwd_char = ft_strdup(get_in_env(data->envp, "OLDPWD")); //WHAT????
	chdir(old_cwd_char);
	data->envp = change_in_env(data->envp, old_cwd, "OLDPWD");
	if (option == 1)
	{
		ft_putstr_fd(old_cwd_char, 1);
		write(1, "\n", 1);
	}
	free (old_cwd_char);
}

void	cd_options_tilde(t_data *data, int exit_flag)
{
	char	cwd[256];

	if (data->token->next->str[0] == '-' && data->token->next->str[1] == '+')
		return (cd_error_invalid_option(data, exit_flag));
	getcwd(cwd, sizeof(cwd));
	if (data->token->next->str[1] == '+') //Vai para o pwd atual e mudar o pwd antigo para o pwd atual
	{
		chdir(cwd);
		data->envp = change_in_env(data->envp, cwd, "OLDPWD");
		data->envp = change_in_env(data->envp, cwd, "PWD");
		return (ft_exit_flag(0, exit_flag, data));
	}
	if (data->token->next->str[1] == '-') // Vai para o OLDPWD e mudar o OLDPWD para o atual PWD
	{
		cd_change_last_oldpwd(data, 0);
		getcwd(cwd, sizeof(cwd));
		data->envp = change_in_env(data->envp, cwd, "PWD");
		return (ft_exit_flag(0, exit_flag, data));
	}
}

void	cd_options(t_data *data, t_token *token, int exit_flag)
{
	char	cwd[256];

	if (token->next->str[1] && (token->next->str[1] != '-' && token->next->str[1] != '+'))
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
	cd_change_last_oldpwd(data, 1); // Se nao entrar em nada, entao "cd -"
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
	char	old_cwd[256];

	getcwd(old_cwd, sizeof(old_cwd));
	if (token->next) //se for "cd ..."
	{
		if (data->token->next->str[0] == '\0')
			return (ft_exit_flag(0, exit_flag, data));
		else if ((data->token->next->str[0] == '-' || data->token->next->str[0] == '~')) //se for "cd -" OU "cd ~-" OU "cd ~+" OU "cd ~"
			return (cd_options(data, token, exit_flag));
		else if (!chdir(data->token->next->str)) //Executar o comando normal "cd src/", caso nao encontre, nao entre
		{
			getcwd(cwd, sizeof(cwd));
			data->envp = change_in_env(data->envp, old_cwd, "OLDPWD");
			data->envp = change_in_env(data->envp, cwd, "PWD");
			return (ft_exit_flag(0, exit_flag, data));
		}
		else if (data->token->next && data->token->next->next) // Se for "cd a b"
			return (print_error_flag(ERROR_CD_MANY_ARGUMENT, 1,
				data, exit_flag));
		else
			return (cd_error_invalid_file(data, exit_flag)); // Se "cd algumacoisa" (nao for um diretorio valido)
	}
	else // se for somente "cd"
		only_cd(data, old_cwd, exit_flag);
}
