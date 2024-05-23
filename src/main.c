#include "../header/minishell.h"

void	search_command(char *buffer, t_data *data)
{
	int i;
	int y;
	int flag;
	t_token *reset_command;

	i = 0;
	y = 0;
	reset_command = data->token;

	get_split(buffer, data);
	while(data->token->str)
	{
		printf("%s\n", data->token->str);
		data->token = data->token->next;
	}
}

// void	define_type(t_data *data)
// {
// 	if (strcmp(data->token->command, "pwd") == 0)
// 		getPWD(data);
// 	else if (strcmp(data->token->command, "cd") == 0)
// 		getCD(data);
// 	else if (strcmp(data->token->command, "echo") == 0)
// 		getECHO(data);
// 	else if (strcmp(data->token->command, "exit") == 0)
// 		exit(1);
// 	else
// 	{
// 		printf("%s: command not found\n", data->token->command);
// 		//EXIT CODE CERTO;
// 		free(data->token);
// 	}
// }	else
// 			{
// 				if (buffer[i])
// 					data->commands->value[y++] = buffer[i];
// 			}
// 			i++;
// 			//y++;
// 		}

// 		while (buffer[i] && flag == 0 && buffer[i] != ' ' && buffer[i] != '\t')
// 			data->commands->value[y++] = buffer[i++];

// 		if(!buffer[i])
// 			break;
// 		if(flag == 0)
// 		{
// 			data->commands = data->commands->next;
// 			init_command(data->commands, buffer);
// 		}
// 	}
// 	data->commands = reset_command;
// }


// void	define_type(t_data *data)
// {
// 	if (strcmp(data->token->command, "pwd") == 0)
// 		getPWD(data);
// 	else if (strcmp(data->token->command, "cd") == 0)
// 		getCD(data);
// 	else if (strcmp(data->token->command, "echo") == 0)
// 		getECHO(data);
// 	else if (strcmp(data->token->command, "exit") == 0)
// 		exit(1);
// 	else
// 	{
// 		printf("%s: command not found\n", data->token->command);
// 		//EXIT CODE CERTO;
// 		free(data->token);
// 	}
// }


void init_commands(char *buffer, t_data *data)
{
	init_data(data, buffer);
	search_command(buffer, data);
	//define_type(data);
}

int main(int argc, char **argv, char **envp)
{
	char	*buffer;
	t_data	*data;

	data = malloc(sizeof(t_data));

	while(1)
	{
		buffer = readline("minishell: ");
		add_history(buffer);
		init_commands(buffer, data);
		//free(data);
	}
} 	