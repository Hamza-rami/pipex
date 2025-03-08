/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:51:11 by hrami             #+#    #+#             */
/*   Updated: 2025/03/07 18:05:21 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_pipe(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (!pipex->pipes)
		return ;
	while (i < pipex->count - 1)
	{
		if (pipex->pipes[i])
			free(pipex->pipes[i]);
		i++;
	}
	free(pipex->pipes);
}

void	create_pipes(t_pipex *pipex)
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

void	child_process(t_pipex *pipex, int i, char *cmd_path, char **envp)
{
	int	j;

	j = 0;
	if (i == 0)
	{
		dup2(pipex->f1, 0);
		dup2(pipex->pipes[i][1], 1);
	}
	else if (i == pipex->count - 1)
	{
		dup2(pipex->pipes[i - 1][0], 0);
		dup2(pipex->f2, 1);
	}
	else
	{
		dup2(pipex->pipes[i - 1][0], 0);
		dup2(pipex->pipes[i][1], 1);
	}
	while (j < pipex->count - 1)
	{
		close(pipex->pipes[j][0]);
		close(pipex->pipes[j][1]);
		j++;
	}
	execute_command(cmd_path, pipex->cmd1, envp);
}

void	handle_file(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->count)
	{
		wait(NULL);
		i++;
	}
	close(pipex->f1);
	close(pipex->f2);
	if (pipex->cmd1)
		free_split(pipex->cmd1);
	if (pipex->cmd_paths)
		free(pipex->cmd_paths);
	if (pipex->paths)
		free_split(pipex->paths);
	free_pipe(pipex);
}
