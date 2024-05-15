#include "../header/minishell.h"

void	search_command(char *buffer, t_data *data)
{
	int i;
	int y;

	i = 0;
	y = 0;
	while(buffer[i] == ' ' || buffer[i] == '\t')
		i++;
	while(buffer[i] && (buffer[i] != ' ' && buffer[i] != '\t' && buffer[i] != '\n'))
	{
		data->command->command[y] = buffer[i];
		i++;
		y++;
	}
}

int	fft_strncmp(const char *s1, const char *s2, size_t n)
{
	int				i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if ((int)n < 0)
		return ((int)n);
	while ((str1[i] || str2[i]) && i < (int)n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

void	define_type(t_data *data)
{
	if (fft_strncmp(data->command->command, "pwd", ft_strlen("pwd")) == 0)
		data->command->type = pwd;
	else if (fft_strncmp(data->command->command, "cd", ft_strlen("cd")) == 0)
		data->command->type = cd;
}

void	check_command(t_data *data)
{
	if(data->command->type == pwd)
		getPWD();
	else if (data->command->type == cd)
		printf("this is a cd\n");
}

void init_commands(int fd, char *buffer, t_data *data)
{
	read(1, buffer, 15);
	//buffer = "pwd";
	search_command(buffer, data);
	define_type(data);
	check_command(data);
	//free(buffer);
}

int main(int argc, char **argv)
{
	char	*buffer;
	t_data	*data;
	char cwd[PATH_MAX];
	buffer = ft_calloc(1, BUFFER_SIZE);
	data = (t_data *)malloc(sizeof(t_data));
	init_data(data);
	//	data->command->command = ft_calloc(1, 1);

	int fd = open("teste.txt", O_RDONLY);
	//buffer = "pwd";



	//getcwd(cwd, sizeof(cwd));
	// buffer = ft_calloc(1, ft_strlen(argv[2]));
	// //init_commands(buffer, commands);

	// 	read(1, buffer, 10);
	// 	printf("%s\n", buffer);
	// 	printf("a");
	// while(1)
	// {
	// 	init_commands(fd, buffer, commands);
	// 	//pause();
	// }
	while(1)
	{
		init_commands(1, buffer, data);
		//pause();
	}
	//printf("%s\n", cwd);
} 	