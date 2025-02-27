/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 11:10:35 by hrami             #+#    #+#             */
/*   Updated: 2025/02/25 15:05:07 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_pipex
{
	int		**pipes;
	int		count;
	int		f1;
	int		f2;
}	t_pipex;

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*get_envp(char *envp[]);
char	*find_command(char **split_paths, char *cmd);
void	check_command(t_pipex *pipex, char **envp);
void	free_split(char **str);
char	*ft_strdup(char *src);
#endif