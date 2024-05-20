#include "../header/minishell.h"

void	search_command(char *buffer, t_data *data)
{
	int i;
	int y;
	int flag;
	t_command *reset_command;

	i = 0;
	y = 0;
	flag = 0;
	reset_command = data->command;

	while(buffer[i] == ' ' || buffer[i] == '\t')
		i++;
	while(buffer[i] && (buffer[i] != ' ' && buffer[i] != '\t' && buffer[i] != '\n'))
		data->command->command[y++] = buffer[i++];
	
	while (buffer[i])
	{
		y = 0;
		while(buffer[i] == ' ' || buffer[i] == '\t' || buffer[i] == 39 || buffer[i] == 34)
		{
			if(buffer[i] == 39)
				flag = 1;
			else if (buffer[i] == 34)
				flag = 2;
			i++;
		}
		while(buffer[i] && (buffer[i] != ' ' && buffer[i] != '\t' && buffer[i] != '\n'))
		{
			//printf("%d\n", flag);
			if(flag == 1)
			{
				while (buffer[i] && buffer[i] != 39)
					data->command->value[y++] = buffer[i++];
			}
			else if (flag == 2)
			{
				while (buffer[i] && buffer[i] != 34)
					data->command->value[y++] = buffer[i++];
			}
		}

		while (buffer[i] && flag != 0 && buffer[i] != 39 && buffer[i] != 34)
			data->command->value[y++] = buffer[i++];

		if(!buffer[i])
			break;
		if(flag = 0)
		{
			data->command = data->command->next;
			init_command(data->command, buffer);
		}
	}
	data->command = reset_command;
}


void	define_type(t_data *data)
{
	if (strcmp(data->command->command, "pwd") == 0)
		getPWD(data);
	else if (strcmp(data->command->command, "cd") == 0)
		getCD(data);
	else if (strcmp(data->command->command, "echo") == 0)
		getECHO(data);
	else if (strcmp(data->command->command, "exit") == 0)
		exit(1);
	else
	{
		printf("command not yet builded\n");
		free(data->command);
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