/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouza-o <nsouza-o@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:24:21 by nsouza-o          #+#    #+#             */
/*   Updated: 2024/05/24 20:23:02 by nsouza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*s;

	s = malloc(n * size);
	if (!s)
		return (NULL);
	ft_bzero(s, n * size);
	return (s);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = '\0';
		i++;
	}
}

size_t	ft_strlen(const char *str)
{
	int		i;
	char	*s;

	s = (char *)str;
	i = 0;
	while (s[i])
		i++;
	return (i);
}



/* -------- */

t_envp	*ft_lstnew_env(void *key, void *value)
{
	t_envp	*list;

	list = ft_calloc(sizeof(t_list), 1);
	if (!list)
		return (0); // 
	list->key = key;
	list->value = value;
	list->next = NULL;
	return (list);
}

void	cpy_env(t_envp *env, char *str)
{
	int		i;
	int		j;
	char	*key;
	char	*value;
	int 	size;
	
	i = -1;
	j = -1;
	(void)env;
	while (str[++i] && str[i] != '=')
		;
	key = ft_calloc(sizeof(char), (i + 1));
	size = ft_strlen(str) - i;
	value = ft_calloc(sizeof(char), size);
	i = -1;
	while(str[++i] && (str[i] != '='))
		key[i] = str[i];
	while(str[++i])
		value[++j] = str[i];
	ft_lstnew_env(key, value);
	
	lst_env(value, key, )
	printf("%s\n", key);
	printf("%s\n", value);
}

/* void	get_env(t_data *data, char **env)
{
	int		i;

	i = -1;
	while (env[++i])
	{
		cpy_env(data->envp, env[i]);
	}
	return (NULL);
} */

int main(int ac, char **av, char **envp)
{
	int		i;

	(void)ac;
	(void)av;
	i = -1;
	while (envp[++i])
	{
		cpy_env(NULL, envp[i]);
		
	}
}

