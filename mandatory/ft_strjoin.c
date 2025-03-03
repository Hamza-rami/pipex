/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 11:04:07 by hrami             #+#    #+#             */
/*   Updated: 2025/03/01 10:56:47 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_strcpy(char *dest, char const *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*arr;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	arr = malloc(i + j + 1);
	if (arr == NULL)
		return (NULL);
	ft_strcpy(arr, s1);
	j = 0;
	while (s2[j])
	{
		arr[i + j] = s2[j];
		j++;
	}
	arr[i + j] = '\0';
	return (arr);
}

char	*ft_strdup(char *src)
{
	int		i;
	int		size;
	char	*str;

	size = 0;
	i = 0;
	while (src[size])
	{
		size++;
	}
	str = malloc(size + 1);
	if (str == NULL)
	{
		return (NULL);
	}
	while (src[i])
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	open_file(t_pipex *pipex, char *av[])
{
	pipex->f1 = open(av[1], O_RDONLY);
	if (pipex->f1 < 0)
	{
		free_split(pipex->cmd1);
		free_split(pipex->cmd2);
		perror("Error opening file");
		exit(1);
	}
	pipex->f2 = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->f2 < 0)
	{
		close(pipex->f1);
		free_split(pipex->cmd1);
		free_split(pipex->cmd2);
		perror("Error opening file");
		exit(1);		
	}
	if (pipe(pipex->pip) < 0)
	{
		free_split(pipex->cmd1);
		free_split(pipex->cmd2);
		perror("pipe error");
		exit(1);
	}
}
