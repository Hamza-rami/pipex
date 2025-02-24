/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:58:10 by hrami             #+#    #+#             */
/*   Updated: 2025/02/22 13:34:06 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	help_main(int ac, char **av, char *envp[], t_pipex *pipex)
{
	if (ac != 5)
	{
		perror("Error \n enter the exact number of arguments");
		exit(1);
	}
	if (!envp || !envp[0])
	{
		perror("Error \n no environment variables found");
		exit(1);
	}
	pipex->cmd1 = ft_split(av[2], ' ');
	if (!pipex->cmd1)
	{
		perror("Error\n splite return NULL");
		exit(1);
	}
	pipex->cmd2 = ft_split(av[3], ' ');
	if (!pipex->cmd2)
	{
		free_split(pipex->cmd1);
		perror("Error\n splite return NULL");
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

void	help_close(t_pipex *pipex)
{
	close(pipex->pip[0]);
	close(pipex->pip[1]);
	close(pipex->f1);
	close(pipex->f2);
	waitpid(pipex->pid1, NULL, 0);
	waitpid(pipex->pid2, NULL, 0);
}

void	execute_command(t_pipex *pipex, int is_first, char *envp[])
{
	if (is_first)
	{
		dup2(pipex->f1, 0);
		dup2(pipex->pip[1], 1);
	}
	else
	{
		dup2(pipex->pip[0], 0);
		dup2(pipex->f2, 1);
	}
	close(pipex->pip[0]);
	close(pipex->pip[1]);
	close(pipex->f1);
	close(pipex->f2);
	if (is_first)
		execve(pipex->cmd1_path, pipex->cmd1, envp);
	else
		execve(pipex->cmd2_path, pipex->cmd2, envp);
	perror("execve failed");
	exit(1);
}

int	main(int ac, char *av[], char *envp[])
{
	t_pipex	pipex;

	help_main(ac, av, envp, &pipex);
	check_command(&pipex, envp);
	open_file(&pipex, av);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		execute_command(&pipex, 1, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		execute_command(&pipex, 0, envp);
	help_close(&pipex);
	free_split(pipex.cmd1);
	free_split(pipex.cmd2);
	free(pipex.cmd1_path);
	free(pipex.cmd2_path);
}
