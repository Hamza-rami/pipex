/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 11:04:20 by hrami             #+#    #+#             */
/*   Updated: 2025/03/09 02:29:50 by hrami            ###   ########.fr       */
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

void	help(t_pipex *pipex)
{
	perror("command not found\ncommand not found");
	if (pipex->cmd1)
		free_split(pipex->cmd1);
	if (pipex->cmd2)
		free_split(pipex->cmd2);
	if (pipex->paths)
		free_split(pipex->paths);
	exit(1);
}

void	help_check_command(t_pipex *pipex, char **envp)
{
	if (!pipex->cmd1 || !pipex->cmd1[0])
		return ;
	if (pipex->cmd1[0][0] == '.' || pipex->cmd1[0][0] == '/')
	{
		if (access(pipex->cmd1[0], X_OK) == 0)
			pipex->cmd1_path = ft_strdup(pipex->cmd1[0]);
	}
	else
	{
		get_path(pipex, envp);
		pipex->cmd1_path = find_command(pipex->paths, pipex->cmd1[0]);
	}
}

void	check_command(t_pipex *pipex, char **envp)
{
	help_check_command(pipex, envp);
	if (!pipex->cmd2 || !pipex->cmd2[0])
	{
		if (!pipex->cmd1_path)
			help(pipex);
	}
	else if (pipex->cmd2[0][0] == '.' || pipex->cmd2[0][0] == '/')
	{
		if (access(pipex->cmd2[0], X_OK) == 0)
			pipex->cmd2_path = ft_strdup(pipex->cmd2[0]);
	}
	else
	{
		if (pipex->paths)
			free_split(pipex->paths);
		get_path(pipex, envp);
		pipex->cmd2_path = find_command(pipex->paths, pipex->cmd2[0]);
	}
	if (!pipex->cmd2_path && !pipex->cmd1_path)
		help(pipex);
}
