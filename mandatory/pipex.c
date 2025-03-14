/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:58:10 by hrami             #+#    #+#             */
/*   Updated: 2025/03/09 02:22:59 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	help_main(int ac, char **av, t_pipex *pipex)
{
	if (ac != 5)
	{
		perror("Error \n enter the exact number of arguments");
		exit(1);
	}
	pipex->cmd1 = ft_split(av[2], ' ');
	pipex->cmd2 = ft_split(av[3], ' ');
}

void	help_close(t_pipex *pipex)
{
	close(pipex->pip[0]);
	close(pipex->pip[1]);
	waitpid(pipex->pid1, NULL, 0);
	waitpid(pipex->pid2, NULL, 0);
}

void	execute_first(t_pipex *pipex, char *envp[], char *infile)
{
	pipex->f1 = open(infile, O_RDONLY);
	if (pipex->f1 < 0)
	{
		perror("Error opening file");
		close(pipex->pip[0]);
		close(pipex->pip[1]);
		free_resorce(pipex);
		exit(1);
	}
	dup2(pipex->f1, 0);
	dup2(pipex->pip[1], 1);
	close(pipex->pip[0]);
	close(pipex->pip[1]);
	close(pipex->f1);
	if (!pipex->cmd1_path)
	{
		free_resorce(pipex);
		perror("command not found");
		exit(1);
	}
	execve(pipex->cmd1_path, pipex->cmd1, envp);
	perror("execve failed");
	exit(1);
}

void	execute_second(t_pipex *pipex, char *envp[], char *outfile)
{
	pipex->f2 = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->f2 < 0)
	{
		perror("Error opening file");
		free_resorce(pipex);
		exit(1);
	}
	dup2(pipex->pip[0], 0);
	dup2(pipex->f2, 1);
	close(pipex->pip[0]);
	close(pipex->pip[1]);
	close(pipex->f2);
	if (!pipex->cmd2_path)
	{
		free_resorce(pipex);
		perror("command not found");
		exit(1);
	}
	execve(pipex->cmd2_path, pipex->cmd2, envp);
	perror("execve failed");
	exit(1);
}

int	main(int ac, char *av[], char *envp[])
{
	t_pipex	pipex;

	help_main(ac, av, &pipex);
	pipex.paths = NULL;
	pipex.cmd1_path = NULL;
	pipex.cmd2_path = NULL;
	check_command(&pipex, envp);
	if (pipex.paths)
		free_split(pipex.paths);
	creat_pip(&pipex);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		execute_first(&pipex, envp, av[1]);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		execute_second(&pipex, envp, av[4]);
	help_close(&pipex);
	free_split(pipex.cmd1);
	free_split(pipex.cmd2);
	free(pipex.cmd1_path);
	free(pipex.cmd2_path);
}
