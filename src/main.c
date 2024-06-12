/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:20:02 by bde-souz          #+#    #+#             */
/*   Updated: 2024/06/12 13:01:40 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	G_EXIT_CODE;

char	*ft_strjoin_free(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*join;

	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	i = ft_strlen(s1);
	j = 0;
	join = (char *)malloc(sizeof(s1[0]) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (join == NULL)
		return (NULL);
	while (s1[j])
	{
		join[j] = s1[j];
		j++;
	}
	j = -1;
	while (s2[++j])
		join[i + j] = s2[j];
	free(s1);
	join[i + j] = '\0';
	return (join);
}

char *put_space_on_pipes(char *buffer, int i)
{
    char *new_buffer;
    char *temp;

    new_buffer = ft_calloc(sizeof(char), i + 1);
    if (!new_buffer)
        return NULL;
    ft_strlcpy(new_buffer, buffer, i + 1);
    temp = ft_strjoin_free(new_buffer, " | ");
    if (!temp)
    {
        free(new_buffer);
        return NULL;
    }
    new_buffer = ft_strjoin_free(temp, buffer + i + 1);
    if (!new_buffer)
    {
        free(temp);
        return NULL;
    }
    free(buffer);
    return (new_buffer);
}


/* char	*put_space_on_pipes(char *buffer, int i)
{
	char	*new_buffer;

	new_buffer = ft_calloc(sizeof(char), i + 1);
	ft_strlcpy(new_buffer, buffer, i);
	new_buffer = ft_strjoin_free(new_buffer, " | ");
	new_buffer = ft_strjoin_free(new_buffer, buffer + i + 1);
	free(buffer);
	return (new_buffer);
} */

char	*checks_pipes(char *buffer)
{
	int	i;
	int quote_flag;

	quote_flag = 1;
	i = -1;
	while (buffer[++i])
	{
		if (buffer[i] == D_QUOTES || buffer[i] == S_QUOTES)
			quote_flag *= -1;
		if (buffer[i] == '|' && quote_flag > 0)
		{
			buffer = put_space_on_pipes(buffer, i);
			i += 2;	
		}
	}
	return (buffer);
}

void	search_command(char *buffer, t_data *data) // FUNC separar o buffer em tokens
{
	buffer = checks_pipes(buffer);
	get_split(buffer, data);
	//check_tokens(data);
	//debug_print_list(data); // DEBUG PARA LER A LISTA COMPLETA
	//free_all(data);
}

void	use_command(t_data *data) // Func para buscar qual tipo de <type>
{
	if(data->token->type == builtin)
		get_builtin(data);
}

void	debug_print_list_ex(t_data *data)
{
	int			i;
	t_token		*temp_token;

	i = 0;
	temp_token = data->token;
	while (data->token->str)
	{
		printf(C_BLUE"Node:"END_COLOR C_GREEN" %d "END_COLOR, i++);
		printf(C_RED"-"END_COLOR"%s"C_RED"-\n"END_COLOR, data->token->str);
		printf("type: %d\n", data->token->type);
		printf("builtin: %d\n\n\n", data->token->builtin);
		
		data->token = data->token->next;
	}
	printf("Error code: %d\n", G_EXIT_CODE);
	data->token = temp_token;
}

void init_commands(char *buffer, t_data *data)
{
	init_data(data, buffer);
	search_command(buffer, data);
	tokenize(data);
	expand(data);
	//debug_print_list_ex(data);
	/* data->token->type = builtin; // retirar
	data->token->builtin = echo;// retirar */
	//use_command(data);
	data->token->type = builtin;
	data = debug_get_builtin_type(data);
	use_command(data);
}

int main(int argc, char **argv, char **envp)
{
	char	*buffer;
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));;
	if (!data)
		return (0);
	get_env(data, envp);
	int i = 0;
	while(1)
	{
		buffer = readline("minishell: ");
		add_history(buffer);
		if (valid_input(buffer))
		{
			G_EXIT_CODE = 0; //#TODO <-- Exit code fica aqui?
			init_commands(buffer, data);
		}
		//ft_free_data(data, 1);
		// i++;
		// if (i == 2)  <-- #TODO Lidar com alocacao do data
		// 	exit (1);
		// data = ft_calloc(1, sizeof(t_data));
		printf("\n$?: %d\n", G_EXIT_CODE); //<-- verificar o ultimo exit code
	}
}

