/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_first.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:28:38 by bde-souz          #+#    #+#             */
/*   Updated: 2024/07/22 15:08:28 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

bool	syntax_error_sup (char *buffer, t_data *data)
{
	if (buffer[0] == '|')
	{
		if (buffer[1] == '|')
			print_error(ERROR_PIPE_DOUBLE, 2, data);
		else
			print_error(ERROR_PIPE_SINGLE, 2, data);
		return (true);
	}
	else if (redirect_error(buffer))
		return (true);
	else if (redirect_inverse_error(buffer))
		return (true);
	else if (redirect_space_and_count_error(buffer))
		return (true);
	else if (ft_strchr("|<>", buffer[ft_strlen(buffer) - 1]))
	{
		if (buffer[ft_strlen(buffer) - 1] == '|')
			print_error(ERROR_PIPE_FINAL, 1, data);
		else
			print_error(ERROR_REDIR, 2, data);
		return (true);
	}
	return (false);
}

bool	check_for_quotes(char *buffer, t_data *data) // Procura por D_QUOTES ou S_QUOTES nao fechadas
{
	int s_quotes;
	int d_quotes;
	int i;
	
	i = 0;
	s_quotes = 0;
	d_quotes = 0;
	while(buffer[i])
	{
		if (buffer[i] == S_QUOTES && !d_quotes)
			s_quotes = !s_quotes;
		else if (buffer[i] == D_QUOTES && !s_quotes)
			d_quotes = !d_quotes;
		i++;
	}
	if (d_quotes != 0 || s_quotes != 0)
	{
		print_error(ERROR_QUOTE, 1, data);
		return (true);
	}
	return (false);
}

bool	check_for_double_pipes(char *buffer)
{
	int i;
	bool in_quotes;

	i = 0;
	in_quotes = false;
	while(buffer[i])
	{
		if(buffer[i] == '\'')
			in_quotes = !in_quotes;
		if(!in_quotes && buffer[i] == '|')
		{
			i++;
			while(buffer[i] == ' ')
				i++;
			if(buffer[i] == '|')
				return true;
			else
				return false;
		}
		i++;
	}
	return false;
}


bool	check_for_syntax_error(char *buffer, t_data *data)
{
	buffer = ft_strtrim(buffer, " \t");
	if (!buffer || first_character(buffer) //ft_strchr("|<>", buffer[0])
		|| ft_strchr("|<>", buffer[ft_strlen(buffer) - 1]))
	{
		if (buffer)
			if (syntax_error_sup(buffer, data))
				data->exit_code = 2;
		free (buffer);
		return (false);
	}
	if (buffer && syntax_error_sup(buffer, data) == true)
	{
		data->exit_code = 2; //verificar
		free (buffer);
		return (false);
	}
	if (check_for_double_pipes(buffer))
	{
		print_error(ERROR_PIPE_SINGLE, 2, data);
		free(buffer);
		return (false);
	}
	free (buffer);
	return (true);
}

bool	valid_input(char *buffer, t_data *data)
{
	if (!buffer || buffer == NULL)
	{
		free_env(data->envp);
		//free_token(data->token);
		free_data(data);
		ft_putstr_fd("exit\n", 2);
		exit (G_EXIT_CODE);
	}
	if(is_all_space(buffer))
	{
		free(buffer);
		return (false);
	}
	if (check_for_quotes(buffer, data) || !check_for_syntax_error(buffer, data))
	{
		add_history(buffer);
		free(buffer);
		return (false);
	}
	return (true);
}
