#ifndef PIPEX_H
#define PIPEX_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>



char	**ft_split(char const *s, char c);
int     ft_strstr(char *haystack, char *needle);
char	*ft_strjoin(char *s1, char *s2);

#endif