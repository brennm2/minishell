/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_first.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:28:38 by bde-souz          #+#    #+#             */
/*   Updated: 2024/07/11 12:35:05 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

bool	is_all_space(char *buffer)
{
	int i;

	i = 0;
	while(buffer[i++])
		if (buffer[i] != ' ')
			return (false);
	return (true);
}

void	redirect_error_suport(char *buffer, int i)
{
	if (buffer[move_space(buffer, i + 1)] == '<')
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putchar_fd(buffer[move_space(buffer, i + 1)], 2);
		ft_putstr_fd("\'\n", 2);
	}
	else if (buffer[move_space(buffer, i + 1)] == '|')
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putchar_fd(buffer[move_space(buffer, i + 1)], 2);
		ft_putstr_fd("\'\n", 2);
	}
}
void	redirect_inverse_error_suport(char *buffer, int i)
{
	if (buffer[move_space(buffer, i + 1)] == '>')
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putchar_fd(buffer[move_space(buffer, i + 1)], 2);
		ft_putstr_fd("\'\n", 2);
	}
	else if (buffer[move_space(buffer, i + 1)] == '|')
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putchar_fd(buffer[move_space(buffer, i + 1)], 2);
		ft_putstr_fd("\'\n", 2);
	}
}

bool	redirect_error(char *buffer)
{
	bool s_quotes;
	bool d_quotes;
	int i;

	s_quotes = false;
	d_quotes = false;
	i = 0;
	while(buffer[i])
	{
		if (buffer[i] == S_QUOTES)
			s_quotes = !s_quotes;
		else if (buffer[i] == D_QUOTES)
			d_quotes = !d_quotes;
		else if (buffer[i] == '>' && (buffer[move_space(buffer, i + 1)] == '<'
				|| buffer[move_space(buffer, i + 1)] == '|')
				&& !d_quotes && !s_quotes)
		{
			redirect_error_suport(buffer, i);
			return (true);
		}
		i++;
	}
	return (false);
}
bool	redirect_inverse_error(char *buffer)
{
	bool s_quotes;
	bool d_quotes;
	int i;

	s_quotes = false;
	d_quotes = false;
	i = 0;
	while(buffer[i])
	{
		if (buffer[i] == S_QUOTES)
			s_quotes = !s_quotes;
		else if (buffer[i] == D_QUOTES)
			d_quotes = !d_quotes;
		else if (buffer[i] == '<' && (buffer[move_space(buffer, i + 1)] == '>'
				|| buffer[move_space(buffer, i + 1)] == '|')
				&& !d_quotes && !s_quotes && (buffer[i + 1] == ' ' 
				|| buffer[i + 1] == '|'))
		{
			redirect_inverse_error_suport(buffer, i);
			return (true);
		}
		i++;
	}
	return (false);
}

bool	redirect_space_and_count_error(char *buffer)
{
	bool s_quotes;
	bool d_quotes;
	int i;

	s_quotes = false;
	d_quotes = false;
	i = 0;
	while(buffer[i])
	{
		if (buffer[i] == S_QUOTES)
			s_quotes = !s_quotes;
		else if (buffer[i] == D_QUOTES)
			d_quotes = !d_quotes;
		else if (buffer[i] == '>' && buffer[i + 1] == ' '
			&& buffer[move_space(buffer, i + 2)] == '>'
			&& !d_quotes && !s_quotes)
		{
			printf("error\n");
			return (true);
		}
		i++;
	}
	return (false);
}


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
	else
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
		if(!in_quotes && buffer[i] == '|' && buffer[i + 1] != '|')
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

bool	first_character(char *buffer)
{
	//ft_strchr("|<>", buffer[0]) 
	if (ft_strchr("|<>", buffer[0]) && is_all_space(buffer))
	{
		return (true);
	}
	return (false);
}


bool	check_for_syntax_error(char *buffer, t_data *data)
{
	buffer = ft_strtrim(buffer, " \t");
	if (!buffer || first_character(buffer) //ft_strchr("|<>", buffer[0])
		|| ft_strchr("|<>", buffer[ft_strlen(buffer) - 1]))
	{
		if (buffer)
			syntax_error_sup(buffer, data);
		free (buffer);
		return (false);
	}
	if (buffer && syntax_error_sup(buffer, data) == true)
	{
		free (buffer);
		return (false);
	}
	if(check_for_double_pipes(buffer))
	{
		print_error(ERROR_PIPE_SINGLE, 2, data);
		free(buffer);
		return (false);
	}
	free (buffer);
	return (true);
}

// bool	redirect_count(char *buffer)
// {
// 	bool s_quotes;
// 	bool d_quotes;
// 	int i;
// 	int red_count;

// 	s_quotes = false;
// 	d_quotes = false;
// 	i = 0;
// 	red_count = 0;
// 	while(buffer[i])
// 	{
// 		if (buffer[i] == S_QUOTES)
// 			s_quotes = !s_quotes;
// 		else if (buffer[i] == D_QUOTES)
// 			d_quotes = !d_quotes;
// 		else if ((buffer[i] == '>' || buffer[i] == '<') && !d_quotes && !s_quotes)
// 			red_count++;
// 		if (red_count > 2)
// 		{
// 			printf("error red count: %d\n", red_count);
// 			return (true);
// 		}
// 		i++;
// 	}
// 	return (false);
// }


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
	if(is_all_space(buffer) || check_for_quotes(buffer, data)
		|| !check_for_syntax_error(buffer, data)) // retirar o "redirect_count"
		{
			free(buffer);
			return (false);
		}
	return (true);
}