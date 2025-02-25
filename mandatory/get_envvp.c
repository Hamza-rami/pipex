/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envvp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 11:04:20 by hrami             #+#    #+#             */
/*   Updated: 2025/02/24 21:32:26 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	help(t_pipex *pipex, char **paths)
{
	printf("command not found: %s\n", pipex->cmd2[0]);
	free(pipex->cmd1_path);
	free_split(paths);
	free_split(pipex->cmd1);
	free_split(pipex->cmd2);
	exit(1);
}

void	help_check_command(t_pipex *pipex, char **paths)
{
	if (!paths)
	{
		perror("Error: Failed to get paths");
		exit(1);
	}
	if (!pipex->cmd1 || !pipex->cmd1[0])
	{
		perror("Error: Command not found\n");
		free_split(paths);
		exit(1);
	}
	if (access(pipex->cmd1[0], X_OK) == 0)
		pipex->cmd1_path = ft_strdup(pipex->cmd1[0]);
	else
		pipex->cmd1_path = find_command(paths, pipex->cmd1[0]);
	if (!pipex->cmd1_path)
	{
		printf("command not found: %s\n", pipex->cmd1[0]);
		free_split(pipex->cmd1);
		free_split(pipex->cmd2);
		free_split(paths);
		exit(1);
	}
}

void	check_command(t_pipex *pipex, char **envp)
{
	char	*env;
	char	**paths;

	env = get_envp(envp);
	if (!env)
	{
		perror("Error: No environment variables");
		exit(1);
	}
	paths = ft_split(env, ':');
	help_check_command(pipex, paths);
	if (!pipex->cmd2 || !pipex->cmd2[0])
	{
		perror("Error: Command not found\n");
		free_split(paths);
		exit(1);
	}
	if (access(pipex->cmd2[0], X_OK) == 0)
		pipex->cmd2_path = ft_strdup(pipex->cmd2[0]);
	else
		pipex->cmd2_path = find_command(paths, pipex->cmd2[0]);
	if (!pipex->cmd2_path)
		help(pipex, paths);
	free_split(paths);
}
