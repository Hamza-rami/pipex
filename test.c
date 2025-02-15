#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	int p[2];
	int i;
	int f;
	char str[11];

	i = pipe(p);
	if( i < 0)
	{
		perror("error no pipe\n");
		return (0);
	}
	f = fork();
	dup2(p[1], 1);
	if (f == 0)
	{
		close(p[1]);
		read(p[0], str, 10);
		str[10] = '\0';
		printf("%s", str);
	}
	else
	{
		close(p[0]);
		write(p[1], "hiim rami", 10);
	}
	return 0;
}
