/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:50:20 by bde-souz          #+#    #+#             */
/*   Updated: 2024/06/04 17:00:02 by bde-souz         ###   ########.fr       */
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
			free(temp_envp->value);
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

void	get_cd(t_data *data)
{
	//#TODO Fazer o get_cd // "cd - " DONE?//
	char	cwd[256];
	char	old_cwd[256];
	char	test[256];
	t_token *temp_token;

	temp_token = data->token;
	
	getcwd(old_cwd, sizeof(old_cwd));
	printf("Diretorio atual: %s\n", old_cwd);
	
	if(ft_strcmp(data->token->next->str, "-") == 0) //se for > cd -
	{
		chdir(get_in_env(data->envp, "OLDPWD"));
		getcwd(test, sizeof(test));
		printf("Diretorio apos comando: %s\n", test);
	}
	else if (!chdir(temp_token->next->str)) //Se nao achar o diretorio, nao entra
	{
		getcwd(cwd, sizeof(cwd));
		printf("Diretorio apos comando: %s\n", cwd);
		data->envp = change_in_env(data->envp, old_cwd, "OLDPWD");
	}
	else
	{
		printf("error!\n");
	}
}

