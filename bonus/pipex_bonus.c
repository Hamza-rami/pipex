/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:58:10 by hrami             #+#    #+#             */
/*   Updated: 2025/02/24 19:33:37 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	help_main(int ac, char **av, char *envp[], t_pipex *pipex)
{
	if (!envp || !envp[0])
	{
		perror("Error \n no environment variables found");
		exit(1);
	}
	pipex->cmd1 = ft_split(av[2], ' ');
	if (!pipex->cmd1)
	{
		perror("Error\n splite return NULL");
		exit(1);
	}
	pipex->cmd2 = ft_split(av[3], ' ');
	if (!pipex->cmd2)
	{
		free_split(pipex->cmd1);
		perror("Error\n splite return NULL");
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

int	main(int ac, char *av[], char *envp[])
{
	t_pipex	pipex;

	help_main(ac, av, envp, &pipex);
	
}
