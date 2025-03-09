/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 11:10:35 by hrami             #+#    #+#             */
/*   Updated: 2025/03/09 02:08:11 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_pipex
{
	int		**pipes;
	int		count;
	int		f1;
	int		f2;
	char	**paths;
	char	**cmd1;
	int		here_doc;
	char	*cmd_paths;
}	t_pipex;

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*get_envp(char *envp[]);
char	*find_command(char **split_paths, char *cmd);
char	*check_command(t_pipex *pipex, char **envp);
void	get_paths(t_pipex *pipex, char **envp);
void	free_split(char **str);
char	*ft_strdup(char *src);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
void	free_pipe(t_pipex *pipex);
void	handle_here_doc(char *limiter, t_pipex *pipex);
void	open_files_here_doc(t_pipex *pipex, char *outfile);
void	free_pipe(t_pipex *pipex);
void	create_pipes(t_pipex *pipex);
void	child_process(t_pipex *pipex, int i, char **av, char **envp);
void	open_outfile(t_pipex *pipex, char *outfile);
void	execute_command(char *cmd_path, char **cmd, char **envp);
void	handle_file(t_pipex *pipex);
char	*ft_strncpy(char *dest, char const *src, unsigned int n);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(char *src);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*get_next_line(int fd);
int		ft_strlen(char *s);

#endif