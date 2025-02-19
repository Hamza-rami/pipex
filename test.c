#include "pipex.h"

int main(int ac, char *av[])
{
	char	*file1;
	char	*file2;
	char	**cmd1;
	char	**cmd2;
	int		pip[2];

	if(ac != 5)
	{
		perror("Error \n enter the argument exact");
		exit(0);
	}
	file1 = av[1];
	cmd1 = ft_split(av[2], ' ');
	cmd2 = ft_split(av[3], ' ');
	file2 = av[4];  
	// check is command found
	
	return (0);
}
