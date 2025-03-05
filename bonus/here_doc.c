#include "pipex_bonus.h"

void handle_here_doc(char *limiter, t_pipex *pipex)
{
    int     fd[2];
    char    *line;

    if (pipe(fd) == -1)
    {
        perror("pipe failed");
        exit(1);
    }
    write(1, "here_doc> ", 10);
    while ((line = get_next_line(0)))
    {
        if (!ft_strncmp(line, limiter, ft_strlen(limiter)) || !line)
        {
            if (line)
                free(line);
            break;
        }
        write(fd[1], line, ft_strlen(line));
        free(line);
        write(1, "here_doc> ", 10);
    }
    close(fd[1]);
    pipex->f1 = fd[0];
}

void open_files_here_doc(t_pipex *pipex, char *outfile)
{
    pipex->f2 = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (pipex->f2 < 0)
    {
        perror("Error opening output file");
        exit(1);
    }
	pipex->pipes = malloc((pipex->count - 1) * sizeof(int *));
	if (!pipex->pipes)
	{
		perror("Pipe allocation failed");
		exit(1);
	}
}
