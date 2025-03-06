/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:58:10 by hrami             #+#    #+#             */
/*   Updated: 2025/03/05 23:52:27 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	multiple_command(int ac, t_pipex *pipex, char *av[])
{
	if (ac < 5)
	{
		perror("Usage: ./pipex infile cmd1 cmd2 ... cmdn outfile\n");
		exit(1);
	}
	pipex->here_doc = 0;
	open_files(pipex, av[1], av[ac - 1]);
	pipex->count = ac - 3;
	pipex->pipes = malloc((pipex->count - 1) * sizeof(int *));
	if (!pipex->pipes)
	{
		perror("Pipe allocation failed");
		exit(1);
	}
}

void	hr_doc_help(int ac, t_pipex *pipex, char *av[])
{
	if (ac < 6)
	{
		perror("Usage: ./pipex here_doc LIMITER cmd1 cmd2 ... outfile\n");
		exit(1);
	}
	pipex->here_doc = 1;
	handle_here_doc(av[2], pipex);
	pipex->count = ac - 4;
	open_files_here_doc(pipex, av[ac - 1]);
}

void	help(int ac, char **av, char **envp, t_pipex *pipex)
{
	int		i;

	i = 0;
	create_pipes(pipex);
	get_paths(pipex, envp);
	pipex->cmd1 = NULL;
	pipex->cmd_paths = NULL;
	while (i < pipex->count)
	{
		if (fork() == 0)
		{
			if (pipex->cmd1)
				free_split(pipex->cmd1);
			if (pipex->here_doc == 1)
				pipex->cmd1 = ft_split(av[i + 3], ' ');
			else
				pipex->cmd1 = ft_split(av[i + 2], ' ');
			if (pipex->cmd_paths)
				free(pipex->cmd_paths);
			pipex->cmd_paths = check_command(pipex, envp);
			child_process(pipex, i, pipex->cmd_paths, envp);
		}
		i++;
	}
}

void	handle_file(t_pipex *pipex)
{
	close(pipex->f1);
	close(pipex->f2);
	if (pipex->cmd1)
		free_split(pipex->cmd1);
	if (pipex->cmd_paths)
		free(pipex->cmd_paths);
	free_split(pipex->paths);
	free_pipe(pipex);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;
	int		i;

	if (!ft_strncmp(av[1], "here_doc", 9))
		hr_doc_help(ac, &pipex, av);
	else
		multiple_command(ac, &pipex, av);
	help(ac, av, envp, &pipex);
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
	handle_file(&pipex);
	return (0);
}
