/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_export_utils_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:10:58 by bde-souz          #+#    #+#             */
/*   Updated: 2024/07/12 18:26:25 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

bool	check_invalid_token(t_token *token)
{
	while (token->next && token->next->type == string)
	{
		if (!is_invalid_token(token->next->str))
			return (true);
		token = token->next;
	}
	return (false);
}

// bool	append_in_export(t_data *data, char *key, char *value, int ap_flag)
// {
// 	(void) ap_flag;
// 	(void) value;
	
// 	char *value_ap;
	
// 	key[ft_strlen(key) - 1] = '\0'; //TODO Verficiar isso se pode
// 	if (get_in_env(data->envp, key) == NULL) // Se procurou na lista e não encontrou, então retorna falso
// 	{
// 		return (false);
// 	}
// 	if (ft_strcmp(key, get_in_env(data->envp, key))) // Se achar Key igual no env
// 	{
// 		value_ap = ft_strdup(get_in_env(data->envp, key));
// 		value_ap = ft_strjoin(key, value_ap);
// 		change_in_env(data->envp, value_ap, key);
// 		free(key);
// 		//ft_exit_flag(0, exit_flag, data);
// 		return (true);
// 	}
// 	return (false);
// }