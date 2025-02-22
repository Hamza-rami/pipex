#ifndef PIPEX_H
#define PIPEX_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>



char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char    *get_envp(char *envp[]);
char    *find_command(char **split_paths, char *cmd);
void    check_command(char **cmd1_path, char **cmd2_path, char *cmd1, char *cmd2, char **envp);
void	free_split(char **str);
#endif