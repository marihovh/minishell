#include "../minishell.h"

int main()
{
	// pid_t chd;
	// char *str = NULL;
	// chd = fork();
	if (chdir("/Users/marihovh/Desktop/minishell/ch") != 0)
	{
		printf("Error on changing dir\n");
		exit(1);
	}
	printf("Going to dir: ../ch\n");
	char *path = getcwd(NULL, 15);
	printf("the path: %s\n", path);
	int fd = open("test", O_RDWR);
	int fd2 = dup2()
	if (fd > 0)
	{
		printf("the file is opened\n");
		write(fd, "from original fd\n", 17);
	}else 
		printf("Error\n");
	int fd2 = dup(fd);
	if (fd2 > 0)
	{
		printf("the fle is opened from copied fd\n");
		write(fd2, "from copied fd\n", 15);
	}
	// while(str == NULL || ft_strncmp("C", str, 1) != 0)
	// {
	// 	printf("%s\n", str);
	// 	if (str)
	// 		add_history(str);
	// }
	return (0);
}
