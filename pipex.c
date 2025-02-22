#include "pipex.h"

void help_main(int ac, char **av)
{
	if (ac != 5)
	{
		perror("Error \n enter the exact number of arguments");
		exit(1);
	}
}

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}


void open_file(int *i, int *j, int *f, char *av[])
{
	*i = open(av[1], O_RDONLY);
	*j = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*i < 0 || *j < 0)
	{
		perror("error opening file");
		exit(1);
	}
	*f = fork();
}

void help_close(int i, int j, int f, int f2, int *pip)
{
	close(pip[0]);
	close(pip[1]);
	close(i);
	close(j);
	waitpid(f, NULL, 0);
	waitpid(f2, NULL, 0);
}

int main(int ac, char *av[], char *envp[])
{
	char	**cmd1;
	char	**cmd2;
	int		pip[2];
	int		f;
	int		f2;
	int		j, i;
	char	*cmd1_path;
	char	*cmd2_path;

	help_main(ac, av);
	cmd1 = ft_split(av[2], ' ');
	cmd2 = ft_split(av[3], ' ');
	check_command(&cmd1_path, &cmd2_path, cmd1[0], cmd2[0], envp);
	open_file(&i, &j, &f, av);
	if (pipe(pip) < 0)
	{
		perror("pipe error");
		exit(1);
	}
	if (f == 0)
	{
		dup2(i, 0);
		dup2(pip[1], 1);
		close(pip[1]);
		close(pip[0]);
		close(j);
		execve(cmd1_path, cmd1, envp);
		perror("execve failed");
		exit(1);
	}
	f2 = fork();
	if (f2 == 0)
	{
		dup2(j, 1);
		dup2(pip[0], 0);
		close(pip[1]);
		close(pip[0]);
		close(i);
		execve(cmd2_path, cmd2, envp);
		perror("execve failed");
		exit(1);
	}
	help_close(i, j, f, f2, pip);
	free_split(cmd1);
	free_split(cmd2);
	free(cmd1_path);
	free(cmd2_path);
}
