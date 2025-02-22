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
void f()
{
	system("lsof -c a.out");
}
void check_command(char **cmd1_path, char **cmd2_path, char *cmd1, char *cmd2, char **envp)
{
	char	*env;
	char	**paths;
	atexit(f);
	env = get_envp(envp);
	paths = ft_split(env, ':');

	*cmd1_path = find_command(paths, cmd1);
	if (!*cmd1_path)
	{
		printf("command not found: %s\n", cmd1);
		free_split(paths);
		exit(1);
	}
	*cmd2_path = find_command(paths, cmd2);
	if (!*cmd2_path)
	{
		printf("command not found: %s\n", cmd2);
		free_split(paths);
		exit(1);
	}
	free_split(paths);
}
