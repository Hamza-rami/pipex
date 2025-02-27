/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:58:10 by hrami             #+#    #+#             */
/*   Updated: 2025/02/26 13:40:42 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_pipe(int **tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
void	open_file(t_pipex *pipex, char *av[], int ac)
{
	pipex->f1 = open(av[1], O_RDONLY);
	if (pipex->f1 < 0) {
	    perror("Error opening input file");
	    exit(1);
	}
	pipex->f2 = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->f2 < 0) {
	    perror("Error opening output file");
	    exit(1);
	}
}

void	help_main(int ac, char *av[], char	**envp)
{
	if (ac < 5)
	{
		perror("Error \n no argument");
		exit(1);
	}
	if (!envp || !envp[0])
	{
		perror("Error \n no enveroment");
		exit(1);
	}
}

void	help_pip(t_pipex *pipex)
{
	int i;

	i = 0;
	while (i < pipex->count - 1) 
	{
		if (pipe(pipex->pipes[i]) < 0) 
		{
			perror("Error creating pipe");
			while (i > 0) 
			{
				close(pipex->pipes[i - 1][0]);
				close(pipex->pipes[i - 1][1]);
				i--;
			}
			free_pipe(pipex->pipes, pipex->count - 1);
			exit(1);
		}
		i++;
	}	
}

void	initialize_pipes(t_pipex *pipex, int ac)
{
	int i;
	
	i = 0;
	pipex->count = ac - 3;
	pipex->pipes = malloc(sizeof(int *) * (pipex->count - 1));
	if (!pipex->pipes) {
		perror("Error allocating memory for pipes");
		exit(1);
	}
	while (i < pipex->count - 1)
	{
		pipex->pipes[i] = malloc(sizeof(int) * 2);
		if (!pipex->pipes[i]) 
		{
			perror("Error allocating memory for a pipe");
			while (i > 0)
			{
				free(pipex->pipes[i - 1]);
				i--;
			}
			free(pipex->pipes);
			exit(1);
		}
		i++;
	}
}

int main(int ac, char *av[], char *envp[])
{
    t_pipex pipex;
    int i;
    int pid;

    help_main(ac, av, envp);
    initialize_pipes(&pipex, ac);
    i = 0;
    while (i < pipex.count)
    {
        pid = fork();
        if (pid == 0)	
        {
            if (i == 0)
            {
                dup2(pipex.f1, 0);
                dup2(pipex.pipes[i][1], 1);
                close(pipex.f1);
                close(pipex.f2);
                close(pipex.pipes[i][0]);
                close(pipex.pipes[i][1]);
                char *args[] = {av[i + 2], NULL};
                execve(av[i + 2], args, envp);
            }
            else if (i == pipex.count - 1)
            {
                dup2(pipex.f2, 1);
                dup2(pipex.pipes[i - 1][0], 0);
                close(pipex.f1);
                close(pipex.f2);
                close(pipex.pipes[i - 1][0]);
                close(pipex.pipes[i - 1][1]);
                char *args[] = {av[i + 2], NULL};
                execve(av[i + 2], args, envp);
            }
            else
            {
                dup2(pipex.pipes[i - 1][0], 0);
                dup2(pipex.pipes[i][1], 1);
                close(pipex.f1);
                close(pipex.f2);
                close(pipex.pipes[i][0]);
                close(pipex.pipes[i][1]);
                char *args[] = {av[i + 2], NULL};
                execve(av[i + 2], args, envp);
            }
        }
        i++;
    }
    i = 0;
    while (i < pipex.count)
    {
        waitpid(-1, NULL, 0);
        i++;
    }
    close(pipex.f1);
    close(pipex.f2);
    i = 0;
    while (i < pipex.count - 1)
    {
        close(pipex.pipes[i][0]);
        close(pipex.pipes[i][1]);
        i++;
    }

    return 0;
}


