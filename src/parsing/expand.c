
#include "../../header/minishell.h"

int ft_is_especial(int c)
{
	if ((c >= 33 && c <= 47))
		return (1);
	return (0);
}

int	deal_with_quotes(t_token *token, int i)
{	
	if (token->str[i] == S_QUOTES)
	{
		i++;
		while (token->str[i] != S_QUOTES)
			i++;
	}
	return (i);
}

char	*ft_strjoin_ex(char *s1, char const *s2)
{
	int		strlen;
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	strlen = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (strlen + 1));
	if (!str)
		return (NULL);
	while (s1 && s2)
	{
		while (s1[i])
			str[j++] = s1[i++];
		i = 0;
		while (s2[i])
			str[j++] = s2[i++];
		str[j] = '\0';
		free(s1);
		return (str);
	}
	return (NULL);
}

void	expansion(t_envp *envp, t_token *token, int j, int i)
{
	char	*expanded;

	expanded = ft_calloc(sizeof(char), (j + 1));
	ft_strlcpy(expanded, token->str, j + 1);
	if (envp)
		expanded = ft_strjoin_ex(expanded, envp->value);
	expanded = ft_strjoin_ex(expanded, token->str + i);
	free(token->str);
	token->str = expanded;	
}

void	check_env(t_token *token, t_envp *env, int j, int i)
{
	char *variable;
	int size;
	t_envp *env_aux;

	env_aux = env;
	size = i - j;
	variable = ft_calloc(sizeof(char), size + 1);
	if (!variable)
		exit(1);
	ft_strlcpy(variable, token->str + j + 1, (size));
	while (env_aux)
	{
		if (!ft_strncmp(variable, env_aux->key, size))
		{
			expansion(env_aux, token, j, i);
			free(variable);
			return ;
		}
		env_aux = env_aux->next;
	}
	expansion(NULL, token, j, i);
	free(variable);
}

void	is_expand(t_token *token, t_envp *envp)
{
	int i;
	int j;

	i = -1;
	while (token->str[++i])
	{
		if (token->str[i] == S_QUOTES)
			i = deal_with_quotes(token, i);
		if (token->str[i] == '$')
		{
			j = i;
			while (!ft_is_especial(token->str[++i]) && token->str[i])
				;
			check_env(token, envp, j, i);
			i = -1;
		}
	}
}

void	expand(t_data *data)
{
	t_token *token_aux;

	token_aux = data->token;
	while (token_aux->next)
	{
		is_expand(token_aux, data->envp);
		token_aux = token_aux->next;
	}
}