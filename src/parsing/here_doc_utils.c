/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:39:15 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/07/15 17:51:39 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*expansion_exit_code_hd(char *buffer, int j, int i, char *exit_code)
{
	char	*expanded;

	expanded = ft_calloc(sizeof(char), (j + 1));
	ft_strlcpy(expanded, buffer, j + 1);
	expanded = ft_strjoin_ex(expanded, exit_code);
	expanded = ft_strjoin_ex(expanded, buffer + i + 2);
	free(exit_code);
	free(buffer);
	return (expanded);
}

bool	open_file(char *file)
{
	int	fd;

	if (!file)
		return (false);
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
		return (false);
	close(fd);
	return (true);
}

char	*creat_here_doc_file(int i, int flag)
{
	char	*file;
	char	*nbr;
	char	*temp;
	
	file = NULL;
	nbr = ft_itoa(i);
	temp = ft_strjoin("here_doc_", nbr);
	file = ft_strjoin(temp, ".temp");
	free(nbr);
	free(temp);
	if (flag == 1)
	{
		if (!open_file (file))
		{
			free(file);
			return (NULL);
		}
	}
	return (file);
}

void	write_file(char *here_doc_file, char *buffer)
{
	int	fd;
	
	fd = open(here_doc_file, O_WRONLY | O_APPEND);
	if (fd == -1)
		return ;
	if (buffer)
		write(fd, buffer, ft_strlen(buffer));
	write(fd, "\n", 1);
	close(fd);
}

void	fill_file(t_data *data, char *delimiter, char *here_doc_file, bool flag)
{
	char	*buffer;
	
	while (1)
	{
		buffer = readline("> ");
		if (!ft_strcmp(delimiter, buffer))
		{
			free(buffer);
			free(here_doc_file);
			free(delimiter);	
			clean(data, 0);
		}
		buffer = expand_hd(data, buffer, flag);
		write_file(here_doc_file, buffer);
		free(buffer);
	}	
}