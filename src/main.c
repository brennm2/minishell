#include "../header/minishell.h"

void	search_command(char *buffer, t_commands *commands)
{
	int i;
	int y;

	i = 0;
	y = 0;
	while(buffer[i] == ' ' || buffer[i] == '\t')
		i++;
	while(buffer[i] && (buffer[i] != ' ' || buffer[i] != '\t'))
	{
		commands->commands[y] = buffer[i];
		i++;
		y++;
	}
}

void	check_command(t_commands *commands)
{
	if (commands->commands = "pwd")
		getPWD();
}

int init_commands(char *buffer, t_commands *commands)
{

	search_command(buffer, commands);
	check_command(commands);
	return (1);
}

int main(int argc, char **argv)
{
	char	*buffer;
	t_commands	*commands;
	char cwd[PATH_MAX];



	getcwd(cwd, sizeof(cwd));
	// buffer = ft_calloc(1, ft_strlen(argv[2]));
	// //init_commands(buffer, commands);

	// 	read(1, buffer, 10);
	// 	printf("%s\n", buffer);
	// 	printf("a");
	while(1)
	{
		read(1, buffer, 0);
		if(init_commands() != 0)
		{
			//printf("nao\n");
		}
	}
	printf("%s\n", cwd);
} 	