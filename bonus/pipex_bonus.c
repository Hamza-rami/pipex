/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:58:10 by hrami             #+#    #+#             */
/*   Updated: 2025/03/02 17:39:41 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void free_pipe(int **tab, int size)
{
	int i = 0;
	if (!tab)
		return;
	while (i < size)
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
	free(tab);
}

void help_main(int ac, char *av[], char **envp)
{
	if (ac < 5)
	{
		perror("Error: Not enough arguments");
		exit(1);
	}
	if (!envp || !envp[0])
	{
		perror("Error: No environment variables");
		exit(1);
	}
	if (ac - 3 > 30900)
	{
	perror("Error: Too many commands");
	exit(1);
	}
}

void help_pip(t_pipex *pipex)
{
	int i = 0;
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

void initialize_pipes(t_pipex *pipex, int ac)
{
	int i = 0;
	pipex->count = ac - 3;
	pipex->pipes = malloc(sizeof(int *) * (pipex->count - 1));
	if (!pipex->pipes)
	{
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
				free(pipex->pipes[--i]);
			free(pipex->pipes);
			exit(1);
		}
		i++;
	}
}

void open_file(t_pipex *pipex, char *av[], int ac)
{
	printf("%d\n", pipex->here_doc);
	if (pipex->here_doc == 1)
	{
    	pipex->f2 = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (pipex->f2 < 0)
		{
			perror("Error opening output file");
			exit(1);
		}
	}
	else
	{
		pipex->f1 = open(av[1], O_RDONLY);
		if (pipex->f1 < 0)
		{
			perror("Error opening input file");
			exit(1);
		}
    	pipex->f2 = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pipex->f2 < 0)
		{
			perror("Error opening output file");
			exit(1);
		}
	}
}

void execute_command(char *cmd_path, char **cmd_args, char **envp)
{
	execve(cmd_path, cmd_args, envp);
	perror("execve failed");
	exit(1);
}

void    handle_here_doc(t_pipex *pipex, char *end)
{
	char    *line;

	if (pipe(pipex->hd_pipe) == -1)
	{
		perror("Pipe error");
		exit(1);
	}
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (!line || ft_strncmp(line, end, ft_strlen(end)) == 0)
			break;
		write(pipex->hd_pipe[1], line, ft_strlen(line));
		free(line);
	}
	close(pipex->hd_pipe[1]);
	dup2(pipex->hd_pipe[0], 0);
	close(pipex->hd_pipe[0]);
}

int main(int ac, char *av[], char *envp[])
{
	t_pipex pipex;
	int i;
	int pid;
	int j;
	int	k;
	char    *cmd_paths;
	char	*new_path;
	
	if (ft_strncmp(av[1], "her_doc", 8) == 0)
	{
		pipex.here_doc = 1;
		handle_here_doc(&pipex, av[2]);
	}
	help_main(ac, av, envp);
	initialize_pipes(&pipex, ac);
	help_pip(&pipex);
	open_file(&pipex, av, ac);
	get_paths(&pipex, envp);
	i = 0;
	cmd_paths = NULL;
	pipex.cmd1 = NULL;
	while (i < pipex.count)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("Fork failed");
			exit(1);
		}
		if (pid == 0)
		{
			if (pipex.cmd1)
				free_split(pipex.cmd1);
			if (pipex.here_doc == 1)
				pipex.cmd1 = ft_split(av[i + 3], ' ');
			else
				pipex.cmd1 = ft_split(av[i + 2], ' ');
			new_path = check_command(&pipex, envp);
			if (!new_path)
			{
				free_split(pipex.cmd1);
				free_split(pipex.paths);
				exit(1);
			}
			free(cmd_paths);
			cmd_paths = new_path;
			if (!cmd_paths)
			{
				free_split(pipex.cmd1);
				free_split(pipex.paths);
				free(cmd_paths);
				exit(1);
			}
			if (i == 0)
			{
				if (pipex.here_doc == 1)
				{
					dup2(pipex.hd_pipe[0], 0);
					close(pipex.hd_pipe[0]);
					close(pipex.hd_pipe[1]);
				}
				else
					dup2(pipex.f1, 0);
			}
			else
				dup2(pipex.pipes[i - 1][0], 0);
			if (i == pipex.count - 1)
				dup2(pipex.f2, 1);
			else
				dup2(pipex.pipes[i][1], 1);
			close(pipex.f1);
			close(pipex.f2);
			j = 0;
			while (j < pipex.count - 1)
			{
				close(pipex.pipes[j][0]);
				close(pipex.pipes[j][1]);
				j++;
			}
			execute_command(cmd_paths, pipex.cmd1, envp);    
		}
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
	while (waitpid(-1, NULL, 0) > 0);
	if (pipex.cmd1)
		free_split(pipex.cmd1);
	if (cmd_paths)
		free(cmd_paths);
	free_pipe(pipex.pipes, pipex.count - 1);
	free_split(pipex.paths);
	return 0;
}
