/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:12:37 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/07/13 12:23:47 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	change_token(t_token *token, char *file)
{
	t_token	*dead;
	
	dead = token->next;
	token->next = token->next->next;
	if (token->str)
		free(token->str);
	token->str = ft_strdup(file);
	free(file);
	free_token_redir(dead);
	token->type = here_doc;
}

void	open_here_doc(t_data *data, t_token *token, char *delimiter, bool flag, int i)
{
	char	*here_doc_file;
	int		status;

	here_doc_file = creat_here_doc_file(i, 1);
	if (!here_doc_file)
		clean(data, 1);
	if (safe_fork(data) == 0)
	{
		fill_file(data, delimiter, here_doc_file, flag);
	}
	waitpid(0, &status, 0);
	change_token(token, here_doc_file);
	if (WIFEXITED(status))
		G_EXIT_CODE = WEXITSTATUS(status);
}

char	*erase_the_quote_hd(char *delimiter, int i)
{
	char	*unquote_str;

	unquote_str = ft_calloc(sizeof(char), i + 1);
	ft_strlcpy(unquote_str, delimiter, i + 1);
	i++;
	unquote_str = ft_strjoin_ex(unquote_str, delimiter + i);
	free(delimiter);
	return (unquote_str);
}

char	*remove_quotes_hd(char *delimiter)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (delimiter[i])
	{
		if ((delimiter[i] == S_QUOTES || delimiter[i] == D_QUOTES))
		{
			j = deal_quotes(delimiter, i);
			delimiter = erase_the_quote_hd(delimiter, i);
			delimiter = erase_the_quote_hd(delimiter, j - 1);
			i = j - 1;
		}
		else
			i++;
	}
	return (delimiter);
}

void	is_here_doc(t_data *data)
{
	char	*delimiter;
	t_token	*token_aux;
	bool	flag;
	int		i;

	i = -1;
	token_aux = data->token;
	flag = false;
	while (token_aux)
	{
   		if (!ft_strcmp(token_aux->str, "<<"))
		{
			delimiter = ft_strdup(token_aux->next->str);
			if (ft_strchr(delimiter, '"') || ft_strchr(delimiter, '\''))
			{
				flag = true;
				delimiter = remove_quotes_hd(delimiter);
			}
			open_here_doc(data, token_aux, delimiter, flag, ++i);
			free(delimiter);
			continue ;
		}
		token_aux = token_aux->next;
	}
	return ;
}
