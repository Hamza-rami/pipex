/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:14:50 by hrami             #+#    #+#             */
/*   Updated: 2025/03/08 02:21:39 by hrami            ###   ########.fr       */
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

void	get_path(t_pipex *pipex, char **envp)
{
	char	*env;

	env = get_envp(envp);
	if (!env)
	{
		perror("Error: No environment variables");
		exit(1);
	}
	pipex->paths = ft_split(env, ':');
	if (!pipex->paths)
	{
		perror("Error: Failed to get paths");
		if (pipex->cmd1_path)
			free(pipex->cmd1_path);
		if (pipex->cmd1)
			free_split(pipex->cmd1);
		if (pipex->cmd2)
			free_split(pipex->cmd2);
		exit(1);
	}
}
