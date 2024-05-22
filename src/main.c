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

	i = get_command(buffer, data);
	while(buffer[i] && (buffer[i] >= 7 && buffer[i] <= 32)) // TIRAMOS OS ESPACOS
		i++;
	
	while(buffer[i]) // ENQUANTO AINDA EXISTIR BUFFER (PROCURAR POR FLAGS OU VALUE)
	{
		get_flags(buffer, i, data);
		if(data->token->flag != NULL);
			i = get_flags(buffer, i, data);
		while(buffer[i] && (buffer[i] >= 7 && buffer[i] <= 32)) // TIRAMOS OS ESPACOS
			i++;
		i = get_value(buffer, i, data);

		// {
		// 	i++;
		// 	while(buffer[i] && (buffer[i] != 34 || buffer[i] != 39))
		// 	{
		// 		data->token->value[y++] = buffer[i++];
		// 	}
		// 	data->
		// }
	}

	///split (buffer);
	echo 
	-n
	abc
	
}
// {
// 	int i;
// 	int y;
// 	int flag;
// 	t_commands *reset_command;

// 	i = 0;
// 	y = 0;
// 	flag = 0;
// 	reset_command = data->commands;

// 	while(buffer[i] == ' ' || buffer[i] == '\t')
// 		i++;
// 	while(buffer[i] && (buffer[i] != ' ' && buffer[i] != '\t' && buffer[i] != '\n')) // command
// 		data->commands->command[y++] = buffer[i++];
// 	//getCommand(buffer, data);
	
// 	while (buffer[i]) // value
// 	{
// 		y = 0;
// 		while(buffer[i] == ' ' || buffer[i] == '\t' || buffer[i] == 39 || buffer[i] == 34)
// 		{
// 			if(buffer[i] == 39)
// 			{
// 				flag = 1;
// 				break ;
// 			}
// 			else if (buffer[i] == 34)
// 			{
// 				flag = 2;
// 				break ;
// 			}
// 			i++;
// 		}
// 		while(buffer[i] && flag != 0)
// 		{
// 			//printf("%d\n", flag);
// 			if(flag == 1)
// 			{
// 				if (buffer[i] && buffer[i] != 39)
// 					data->commands->value[y++] = buffer[i];
// 			}
// 			else if (flag == 2)
// 			{
// 				if (buffer[i] && buffer[i] != 34)
// 					data->commands->value[y++] = buffer[i];
// 			}
// 			else
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


void	define_type(t_data *data)
{
	if (strcmp(data->token->command, "pwd") == 0)
		getPWD(data);
	else if (strcmp(data->token->command, "cd") == 0)
		getCD(data);
	else if (strcmp(data->token->command, "echo") == 0)
		getECHO(data);
	else if (strcmp(data->token->command, "exit") == 0)
		exit(1);
	else
	{
		printf("%s: command not found\n", data->token->command);
		//EXIT CODE CERTO;
		free(data->token);
	}
}


void init_commands(char *buffer, t_data *data)
{
	init_data(data, buffer);
	search_command(buffer, data);
	define_type(data);
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