/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:12:37 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/07/10 19:06:53 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	open_here_doc(t_data *data, char *delimiter, bool flag)
{
	char	*buffer;
	int		fd;

	fd = open("here_doc_file", O_WRONLY | O_APPEND);
	//data->fd_here_doc = fd;
	while (1)
	{
		buffer = readline("> ");
		//add_history(buffer);
		if (!ft_strcmp(delimiter, buffer))
		{
			free(buffer);
			break ;
		}
		buffer = expand_hd(data, buffer, flag);
		write(fd, buffer, ft_strlen(buffer));
		free(buffer);
	}	
	close(fd);
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

void	change_token(t_token *token)
{
	char	*new_token_str;
	t_token	*token_aux;

	token_aux = token->next;
	token->next = token->next->next;
	free_token_redir(token_aux);
	new_token_str = ft_strdup("here_doc_file");
	free(token->str);
	token->str = new_token_str;
	token->type = here_doc;
}

void	is_here_doc(t_data *data)
{
	char	*delimiter;
	t_token	*token_aux;
	bool	flag;

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
			open_here_doc(data, delimiter, flag);
			change_token(token_aux);
			free(delimiter);
			return ;
		}
		token_aux = token_aux->next;
	}
	return ;
}