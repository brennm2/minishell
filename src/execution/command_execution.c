/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-souz <bde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 09:48:46 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/07/10 13:45:26 by bde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	count_args(t_data *data)
{
	t_token	*aux;
	int		nbr;

	nbr = 0;
	aux = data->token;
	while (aux)
	{
		if (aux->type == command || aux->type == builtin || aux->type == string)
			nbr++;
		aux = aux->next;
	}
	return (nbr);
}

char	*ft_strdupa(const char *s)
{
	unsigned int	i;
	char			*str;

	i = 0;
	str = (char *)malloc(ft_strlen(s) * sizeof(char) + 1);
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**get_argv(t_data *data)
{
	int		nbr_args;
	int		i;
	char	**argv;
	t_token	*token_aux;
	
	token_aux = data->token;
	nbr_args = count_args(data);
	argv = ft_calloc(nbr_args + 1, sizeof(char *));
	i = -1;
	while (token_aux && ++i < nbr_args)
	{
	argv[i] = ft_strdupa(token_aux->str);
		token_aux = token_aux->next;
	}
	return (argv);
	
}

void	cmd_execution(t_data *data)
{
	int status;
	int pid;
	char	**argv;
	char	*path;
	
	status = 0;
	pid = 0;
	argv = get_argv(data);
	path = get_path(data, argv[0]);
	pid = safe_fork(data);
	ft_signal_ignore(); // Ignora os sinais anteriores
	if (pid == 0)
		safe_execve(data, argv, path);
	waitpid(0, &status, 0);
	G_EXIT_CODE = status; //Verificar
	if (WIFSIGNALED(status) == 1) //Verifica o estado do sinal
		signal_child_checker(status);
	printf("status: %d\n", status); //DEBUG
	printf("exit code: %d\n", G_EXIT_CODE); // DEBUG
	ptr_free(argv);
	free(path);
}
