/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 11:10:35 by hrami             #+#    #+#             */
/*   Updated: 2025/03/08 23:13:23 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_pipex
{
	char	**cmd1;
	char	**cmd2;
	int		pip[2];
	int		f1;
	int		f2;
	int		pid1;
	int		pid2;
	char	*cmd1_path;
	char	*cmd2_path;
	char	**paths;
	int		check;
}	t_pipex;

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*get_envp(char *envp[]);
char	*find_command(char **split_paths, char *cmd);
void	check_command(t_pipex *pipex, char **envp);
void	free_split(char **str);
char	*ft_strdup(char *src);
void	creat_pip(t_pipex *pipex);
void	get_path(t_pipex *pipex, char **envp);
void	free_resorce(t_pipex *pipex);

#endif