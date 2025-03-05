/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:58:10 by hrami             #+#    #+#             */
/*   Updated: 2025/03/04 14:26:51 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void free_pipe(t_pipex *pipex)
{
	int i = 0;

	if (!pipex->pipes)
		return;
	while (i < pipex->count - 1)
	{
		if (pipex->pipes[i])
			free(pipex->pipes[i]);
		i++;
	}
	free(pipex->pipes);
}


void create_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->count - 1)
	{
		pipex->pipes[i] = malloc(2 * sizeof(int));
		if (!pipex->pipes[i])
		{
			perror("Pipe malloc failed");
			free_pipe(pipex);
			exit(1);	
		}
		if (pipe(pipex->pipes[i]) == -1)
		{
			perror("Pipe creation failed");
			while (i-- >= 0)
			{
				close(pipex->pipes[i][0]);
				close(pipex->pipes[i][1]);
			}
			free_pipe(pipex);
			exit(1);
		}
		i++;
	}
}

void open_files(t_pipex *pipex, char *infile, char *outfile)
{
	pipex->f1 = open(infile, O_RDONLY);
	if (pipex->f1 < 0)
	{
		perror("Error opening input file");
		exit(1);
	}
	pipex->f2 = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->f2 < 0)
	{
		perror("Error opening output file");
		exit(1);
	}
}

void execute_command(char *cmd_path, char **cmd, char **envp)
{
	execve(cmd_path, cmd, envp);
	perror("execve failed");
	exit(1);
}

void child_process(t_pipex pipex, int i, char *cmd_path, char **envp)
{
	int j = 0;
	if (i == 0)
	{
		dup2(pipex.f1, 0);
		dup2(pipex.pipes[i][1], 1);
	}
	else if (i == pipex.count - 1)
	{
		dup2(pipex.pipes[i - 1][0], 0);
		dup2(pipex.f2, 1);
	}
	else
	{
		dup2(pipex.pipes[i - 1][0], 0);
		dup2(pipex.pipes[i][1], 1);
	}
	while (j < pipex.count - 1)
	{
		close(pipex.pipes[j][0]);
		close(pipex.pipes[j][1]);
		j++;
	}
	execute_command(cmd_path, pipex.cmd1, envp);
}

void	help(int ac, t_pipex *pipex)
{
	if (ac < 5)
	{
		perror("Usage: ./pipex infile cmd1 cmd2 ... cmdn outfile\n");
		exit(1);
	}
	pipex->count = ac - 3;
	pipex->pipes = malloc((pipex->count - 1) * sizeof(int *));
	if (!pipex->pipes)
	{
		perror("Pipe allocation failed");
		exit(1);
	}
}

int main(int ac, char **av, char **envp)
{
	t_pipex	pipex;
	char	*cmd_paths;
	int		i;
	
	i = 0;
	if (!ft_strncmp(av[1], "here_doc", 8))
	{
	    if (ac < 6)
	    {
	        perror("Usage: ./pipex here_doc LIMITER cmd1 cmd2 ... outfile\n");
	        return (1);
	    }
	    pipex.here_doc = 1;
	    handle_here_doc(av[2], &pipex);
	    pipex.count = ac - 4;
	    open_files_here_doc(&pipex, av[ac - 1]);
	}
	else
	{
	    pipex.here_doc = 0;
	    open_files(&pipex, av[1], av[ac - 1]);
		help(ac, &pipex);
	}
	create_pipes(&pipex);
	get_paths(&pipex, envp);
	pipex.cmd1 = NULL;
	cmd_paths = NULL;
	while (i < pipex.count)
	{
		if (fork() == 0)
		{
			if (pipex.cmd1)
				free_split(pipex.cmd1);
			if (pipex.here_doc == 1)
				pipex.cmd1 = ft_split(av[i + 3], ' ');
			else
				pipex.cmd1 = ft_split(av[i + 2], ' ');
			if (cmd_paths)
				free(cmd_paths);
			cmd_paths = check_command(&pipex, envp);
			child_process(pipex, i, cmd_paths, envp);
		}
		i++;
	}
	i = 0;
	while (i < pipex.count - 1)
	{
		close(pipex.pipes[i][0]);
		close(pipex.pipes[i][1]);
		i++;
	}
	i = 0;
	while (i < pipex.count)
	{
		wait(NULL);
		i++;
	}
	close(pipex.f1);
	close(pipex.f2);
	if (pipex.cmd1)
		free_split(pipex.cmd1);
	if (cmd_paths)
		free(cmd_paths);
	free_split(pipex.paths);
	free_pipe(&pipex);
	return (0);
}
