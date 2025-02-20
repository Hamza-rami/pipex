#include "pipex.h"

int main(int ac, char *av[])
{
	char	*file1;
	char	*file2;
	char	**cmd1;
	char	**cmd2;
	int		pip[2];
	int		f;
	int		f2;
	int		j ,i;

	if(ac != 5)
	{
		perror("Error \n enter the argument exact");
		exit(1);
	}
	file1 = av[1];
	cmd1 = ft_split(av[2], ' ');
	cmd2 = ft_split(av[3], ' ');
	file2 = av[4];
	
	if (pipe(pip) < 0)
		return(printf("pipe error\n"), 0);
	i = open(file1, O_RDONLY);
	j = open(file2,O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (i < 0 || j < 0)
		return(printf("error open file\n"), 0);
	f = fork();
	if (f == 0)
	{
		dup2(i, 0);
		dup2(pip[1], 1);
		close(pip[1]);  
		close(pip[0]);  
		close(j); 
		execve(cmd1[0], cmd1, NULL);
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
		execve(cmd2[0], cmd2, NULL);
		perror("execve failed");
		exit(1);
	}
	close(pip[0]);
	close(pip[1]);
	close(i);
	close(j);
	waitpid(f, NULL, 0);
	waitpid(f2, NULL, 0);
	return (0);
}
