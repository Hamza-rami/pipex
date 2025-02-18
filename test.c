#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main()
{
	int p[2];
	int p2[2];
	int f1, f2, f3;
	char *cmd1[] = {"/bin/ls", "-l", NULL};
	char *cmd2[] = {"/usr/bin/grep", ".c", NULL};
	char *cmd3[] = {"/usr/bin/wc", "-l", NULL};

	if (pipe(p) < 0 || pipe(p2) < 0)
	{
		perror("Pipe error");
		return (1);
	}
	f1 = fork();
	if (f1 == 0)
	{
		dup2(p[1], 1);
		close(p[0]);
		close(p[1]);
		close(p2[0]);
		close(p2[1]);
		execve(cmd1[0], cmd1, NULL);
		perror("execve ls failed");
		return (1);
	}
	f2 = fork();
	if (f2 == 0)
	{
		dup2(p[0], 0);
		dup2(p2[1], 1); 
		close(p[0]);
		close(p[1]);
		close(p2[0]);
		close(p2[1]);
		execve(cmd2[0], cmd2, NULL);
		perror("execve grep failed");
		return (1);
	}
	f3 = fork();
	if (f3 == 0)
	{
		dup2(p2[0], 0);
		close(p2[0]);
		close(p2[1]);
		close(p[0]);
		close(p[1]);
		execve(cmd3[0], cmd3, NULL);
		perror("execve wc failed");
		return (1);
	}
	close(p[0]);
	close(p[1]);
	close(p2[0]);
	close(p2[1]);
	waitpid(f1, NULL, 0);
	waitpid(f2, NULL, 0);
	waitpid(f3, NULL, 0);
	return 0;
}
