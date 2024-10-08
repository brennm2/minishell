/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:31:40 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/08/07 14:33:19 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

char	*expansion_hd(t_envp *envp, char *buffer, int j, int i)
{
	char	*expanded;

	if (!envp && j == 0 && !buffer[i])
		return (NULL);
	expanded = ft_calloc(sizeof(char), (j + 1));
	ft_strlcpy(expanded, buffer, j + 1);
	if (envp)
		expanded = ft_strjoin_ex(expanded, envp->value);
	expanded = ft_strjoin_ex(expanded, buffer + i);
	free(buffer);
	return (expanded);
}

char	*check_env_hd(char *buffer, t_envp *env, int j, int i)
{
	char	*variable;
	int		size;
	t_envp	*env_aux;

	env_aux = env;
	size = i - j;
	variable = ft_calloc(sizeof(char), size + 1);
	if (!variable)
		exit(1);
	ft_strlcpy(variable, buffer + j + 1, (size));
	while (env_aux)
	{
		if (!ft_strncmp(variable, env_aux->key, size))
		{
			buffer = expansion_hd(env_aux, buffer, j, i);
			free(variable);
			return (buffer);
		}
		env_aux = env_aux->next;
	}
	buffer = expansion_hd(NULL, buffer, j, i);
	free(variable);
	return (buffer);
}

char	*expansion_digit_hd(char *buffer, int j, int i)
{
	char	*expanded;

	expanded = ft_calloc(sizeof(char), (j + 1));
	ft_strlcpy(expanded, buffer, j + 1);
	if (buffer[i + 1] == '0')
		expanded = ft_strjoin_ex(expanded, "minishell");
	expanded = ft_strjoin_ex(expanded, buffer + i + 2);
	free(buffer);
	return (expanded);
}

char	*expansion_dollar_sign_hd(char *buffer, int j, int i, int pid)
{
	char	*expanded;
	char	*pid_char;

	pid_char = ft_itoa(pid);
	expanded = ft_calloc(sizeof(char), (j + 1));
	ft_strlcpy(expanded, buffer, j + 1);
	expanded = ft_strjoin_ex(expanded, pid_char);
	expanded = ft_strjoin_ex(expanded, buffer + i + 2);
	free(buffer);
	free(pid_char);
	return (expanded);
}

char	*is_expand_util_hd(char *buffer, t_data *data, int i, int j)
{
	char	*exit_code;

	j = i;
	if (buffer[i + 1] == '?')
	{
		exit_code = ft_itoa(data->exit_code);
		buffer = expansion_exit_code_hd(buffer, j, i, exit_code);
		return (buffer);
	}
	if (buffer[i + 1] == '$')
	{
		buffer = expansion_dollar_sign_hd(buffer, j, i, data->pid);
		return (buffer);
	}
	if (ft_isdigit(buffer[i + 1]))
	{
		buffer = expansion_digit_hd(buffer, j, i);
		return (buffer);
	}
	while (!ft_is_especial(buffer[++i]) && buffer[i] && buffer[i] != 32)
		;
	buffer = check_env_hd(buffer, data->envp, j, i);
	return (buffer);
}
