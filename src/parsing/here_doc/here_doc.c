/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:12:37 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/07/30 15:46:12 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"


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

void	open_hd(t_data *data, t_token *token, char *delimiter, bool flag, int i)
{
	char	*here_doc_file;
	int		status;

	ft_signal_ignore();
	here_doc_file = creat_here_doc_file(i, true);
	if (!here_doc_file)
		clean_hd(data, 1);
	if (safe_fork(data) == 0)
	{
		signal_heredoc(-1, data, delimiter, here_doc_file);
		ft_catch_signal(HERE_DOC);
		fill_file(data, delimiter, here_doc_file, flag);
		clean_hd(data, 0);
	}
	waitpid(0, &status, 0);
	change_token(token, here_doc_file);
	
	if (WIFEXITED(status))
	{
		data->exit_code = WEXITSTATUS(status);
	}
}

char	*erase_the_quote_hd(char *delimiter, int i)
{
	char	*unquote_str;
	char	*temp;

	temp = ft_calloc(sizeof(char), i + 1);
	ft_strlcpy(temp, delimiter, i + 1);
	i++;
	unquote_str = ft_strjoin(temp, delimiter + i);
	free(temp);
	return (unquote_str);
}

char	*remove_quotes_hd(char *delimiter)
{
	int	i;
	int	j;
	char	*temp;

	i = 0;
	j = 0;
	while (delimiter[i])
	{
		if ((delimiter[i] == S_QUOTES || delimiter[i] == D_QUOTES))
		{
			j = deal_quotes(delimiter, i);
			temp = erase_the_quote_hd(delimiter, i);
			free(delimiter);
			delimiter = erase_the_quote_hd(temp, j - 1);
			free(temp);
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
			open_hd(data, token_aux, delimiter, flag, ++i);
			free(delimiter);
			continue ;
		}
		token_aux = token_aux->next;
	}
	return ;
}
