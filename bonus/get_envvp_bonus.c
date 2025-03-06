/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envvp_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 11:04:20 by hrami             #+#    #+#             */
/*   Updated: 2025/03/05 17:34:45 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*get_envp(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A'
			&& envp[i][2] == 'T' && envp[i][3] == 'H' && envp[i][4] == '=')
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

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

void	get_paths(t_pipex *pipex, char **envp)
{
	char	*env;

	env = get_envp(envp);
	if (!env)
	{
		perror("Error: No environment variables");
		free_pipe(pipex);
		exit(1);
	}
	pipex->paths = ft_split(env, ':');
	if (!pipex->paths)
	{
		free_pipe(pipex);
		perror("Error: Failed to get paths");
		exit(1);
	}
}

void	help_check(t_pipex *pipex)
{
	perror("command not found");
	free_split(pipex->cmd1);
	free_split(pipex->paths);
	free_pipe(pipex);
	exit(1);
}

char	*check_command(t_pipex *pipex, char **envp)
{
	char	*cmd_path;

	if (!pipex->cmd1 || !pipex->cmd1[0])
	{
		perror("Error: Command not found\n");
		free_split(pipex->paths);
		free_pipe(pipex);
		exit(1);
	}
	if (pipex->cmd1[0][0] == '.' || pipex->cmd1[0][0] == '/')
	{
		if (access(pipex->cmd1[0], X_OK) == 0)
			cmd_path = ft_strdup(pipex->cmd1[0]);
		else
			cmd_path = NULL;
	}
	else
		cmd_path = find_command(pipex->paths, pipex->cmd1[0]);
	if (!cmd_path)
		help_check(pipex);
	return (cmd_path);
}
