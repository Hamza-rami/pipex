/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:16:12 by hrami             #+#    #+#             */
/*   Updated: 2025/03/05 23:55:58 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	handle_here_doc(char *limiter, t_pipex *pipex)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
	{
		perror("pipe failed");
		exit(1);
	}
	write(1, "here_doc> ", 10);
	line = get_next_line(0);
	limiter = ft_strjoin(limiter, "\n"); //free 
	while (line)
	{
		if (!ft_strncmp(line, limiter, ft_strlen(limiter)) || !line)
		{
			if (line)
				free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
		write(1, "here_doc> ", 10);
		line = get_next_line(0);
	}
	close(fd[1]);
	pipex->f1 = fd[0];
}

void	open_files_here_doc(t_pipex *pipex, char *outfile)
{
	pipex->f2 = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (pipex->f2 < 0)
	{
		close(pipex->f1);
		perror("Error opening output file");
		exit(1);
	}
	pipex->pipes = malloc((pipex->count - 1) * sizeof(int *));
	if (!pipex->pipes)
	{
		//check if u need to close.
		perror("Pipe allocation failed");
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

void	execute_command(char *cmd_path, char **cmd, char **envp)
{
	execve(cmd_path, cmd, envp);
	perror("execve failed");
	exit(1);
}

void	open_files(t_pipex *pipex, char *infile, char *outfile)
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
