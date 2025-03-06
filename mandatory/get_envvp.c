/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envvp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 11:04:20 by hrami             #+#    #+#             */
/*   Updated: 2025/03/05 17:14:46 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_command(char **split_paths, char *cmd)
{
	int		i;
	char	*full_cmd;
	char	*tmp;

	i = 0;
	while (split_paths[i])
	{
		tmp = ft_strjoin(split_paths[i], "/");
		full_cmd = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_cmd, X_OK) == 0)
			return (full_cmd);
		free(full_cmd);
		i++;
	}
	return (NULL);
}

void	help(t_pipex *pipex, char **paths)
{
	perror("command not found");
	free(pipex->cmd1_path);
	free_split(paths);
	free_split(pipex->cmd1);
	free_split(pipex->cmd2);
	exit(1);
}

void	help_check_command(t_pipex *pipex, char **paths)
{
	if (!pipex->cmd1 || !pipex->cmd1[0])
	{
		perror("Error: Command not found\n");
		free_split(paths);
		exit(1);
	}
	if (pipex->cmd1[0][0] == '.' || pipex->cmd1[0][0] == '/')
	{
		if (access(pipex->cmd1[0], X_OK) == 0)
			pipex->cmd1_path = ft_strdup(pipex->cmd1[0]);
		else
			pipex->cmd1_path = NULL;
	}
	else
		pipex->cmd1_path = find_command(paths, pipex->cmd1[0]);
	if (!pipex->cmd1_path)
	{
		perror("command not found");
		free_split(pipex->cmd1);
		free_split(pipex->cmd2);
		free_split(paths);
		exit(1);
	}
}

void	check_command(t_pipex *pipex, char **envp)
{
	get_path(pipex, envp);
	help_check_command(pipex, pipex->paths);
	if (!pipex->cmd2 || !pipex->cmd2[0])
	{
		perror("Error: Command not found\n");
		free_split(pipex->paths);
		exit(1);
	}
	if (pipex->cmd2[0][0] == '.' || pipex->cmd2[0][0] == '/')
	{
		if (access(pipex->cmd2[0], X_OK) == 0)
			pipex->cmd2_path = ft_strdup(pipex->cmd2[0]);
		else
			pipex->cmd2_path = NULL;
	}
	else
		pipex->cmd2_path = find_command(pipex->paths, pipex->cmd2[0]);
	if (!pipex->cmd2_path)
		help(pipex, pipex->paths);
	free_split(pipex->paths);
}
