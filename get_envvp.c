#include "pipex.h"

char    *get_envp(char *envp[])
{
	int i;
	
	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T' && envp[i][3] == 'H')
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char *find_command(char **split_paths, char *cmd)
{
    int i = 0;
    char *full_cmd;
    char *tmp;

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
