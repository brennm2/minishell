/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:50:20 by bde-souz          #+#    #+#             */
/*   Updated: 2024/06/07 11:13:58 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_envp	*change_in_env(t_envp *envp, char *cwd, char *key)
{
	t_envp *temp_envp;
	
	temp_envp = envp;
	while(temp_envp)
	{
		if(ft_strcmp(temp_envp->key, key) == 0)
		{
			printf("oldpwd antes: %s\n", temp_envp->value);
			//free(temp_envp->value);
			temp_envp->value = ft_strdup(cwd);
			printf("oldpwd depois: %s\n", temp_envp->value);
			return (envp);
		}
		temp_envp = temp_envp->next;
	}
	return (envp);
}

char	*get_in_env(t_envp *envp, char *key)
{
	t_envp *temp_envp;

	temp_envp = envp;
	while(temp_envp)
	{
		if(ft_strcmp(temp_envp->key, key) == 0)
			return(temp_envp->value);
		temp_envp = temp_envp->next;
	}
	printf("Nao achou nada\n\n"); //#TODO <--- Apenas para debug, caso nao encontre o que eu quero
	return NULL;
}

void	cd_change_last_oldpwd(t_data *data)
{
	// #TODO 
	// getcwd(old_cwd, sizeof(old_cwd));
	// old_cwd_char = get_in_env(data->envp, "OLDPWD");
	// chdir(old_cwd_char);
	// data->envp = change_in_env(data->envp, old_cwd, "OLDPWD");
	// ft_putstr_fd(old_cwd_char, 1);
	// write(1, "\n", 1);
	// return ;
}

void	cd_options(t_data *data)
{
	char	old_cwd[256];
	char	*old_cwd_char;
	
	if(data->token->next->str[1] && data->token->next->str[1] != '-')
	{
		
		write(2, "minishell: cd: -", 16);
		write(2, &data->token->next->str[1], 1);
		write(2, ": invalid option\n", 17);
		print_error(NULL, 2);
		return ;
	}
	if (data->token->next->str[1] == '-') // se for CD --
	{
		chdir(get_in_env(data->envp, "HOME"));
		return ;
	}
	getcwd(old_cwd, sizeof(old_cwd));
	old_cwd_char = get_in_env(data->envp, "OLDPWD");
	chdir(old_cwd_char);
	data->envp = change_in_env(data->envp, old_cwd, "OLDPWD");
	ft_putstr_fd(old_cwd_char, 1);
	write(1, "\n", 1);
	return ;
}

void	get_cd(t_data *data)
{
	//#TODO Fazer o get_cd // //
	char	cwd[256];
	char	old_cwd[256];
	t_token *temp_token;

	temp_token = data->token;
	getcwd(old_cwd, sizeof(old_cwd));
	printf("\nDiretorio atual: %s\n", old_cwd);
	
	if(data->token->next->str != NULL) //Se existir um proximo <NODE>
	{
		if(data->token->next->str[0] == '-') //se for "cd -""
		{
			cd_options(data);
			return ;
		}
		else if (!chdir(temp_token->next->str)) //Se nao achar o diretorio, nao entra
		{
			getcwd(cwd, sizeof(cwd));
			printf("Diretorio apos comando: %s\n", cwd);
			data->envp = change_in_env(data->envp, old_cwd, "OLDPWD");
			return ;
		}
		else
		{
			write(2, "minishell: cd: ", 15);
			write(2, data->token->next->str, ft_strlen(data->token->next->str));
			write(2, ": No such file or directory\n", 28);
			print_error(NULL, 1);
		}
	}
	else // Se o <NODE> atual for CD e o proximo nao existir
	{
		chdir(get_in_env(data->envp, "HOME"));
		getcwd(cwd, sizeof(cwd));
		printf("Diretorio apos comando: %s\n", cwd);
		return ;
	}
	// write(2, "minishell: cd: ", 15);
	// write(2, data->token->next->str, ft_strlen(data->token->next->str));
	// write(2, ": No such file or directory\n", 28);
	// print_error(NULL, 1);
}

