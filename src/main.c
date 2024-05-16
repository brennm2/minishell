#include "../header/minishell.h"

void	search_command(char *buffer, t_data *data)
{
	int i;
	int y;
	t_data *temp_data;

	i = 0;
	y = 0;
	temp_data = data;
\
	while(buffer[i] == ' ' || buffer[i] == '\t')
		i++;
	while(buffer[i] && (buffer[i] != ' ' && buffer[i] != '\t' && buffer[i] != '\n'))
		data->command->command[y++] = buffer[i++];
	if (buffer[i])
	{
		y = 0;
		while(buffer[i] == ' ' || buffer[i] == '\t')
			i++;
		while(buffer[i] && (buffer[i] != ' ' && buffer[i] != '\t' && buffer[i] != '\n'))
			data->command->value[y++] = buffer[i++];
		data->command = data->command->next;
		if(!buffer[i])
			data->command = temp_data;
	}
	data = temp_data;
}


void	define_type(t_data *data)
{
	if (strcmp(data->command->command, "pwd") == 0)
		getPWD(data);
	else if (strcmp(data->command->command, "cd") == 0)
		getCD(data);
	else if (strcmp(data->command->command, "echo") == 0)
		getECHO(data);
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
	//init_data(data);
	//init_envp

	while(1)
	{
		buffer = readline("minishell: ");
		add_history(buffer);
		init_commands(buffer, data);
		//free(data);
	}
} 	