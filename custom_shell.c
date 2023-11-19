#include "main.h"
#include <stdio.h>

int main(int argc, char **av)
{
	int status;
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	pid_t pid;
	(void)argc;

	while (1)
	{
		printf("#cisfun$ ");

		if ((nread = getline(&line, &len, stdin)) == -1)
		{
			if (feof(stdin))
			{
				printf("\n");
				break;
			}
			else
			{
				perror("getline Error");
				exit(EXIT_FAILURE);
			}
		}

		line[strcspn(line, "\n")] = '\0';

		if (strcasecmp(line, "exit") == 0)
		{
			printf("\n");
			break;
		}

		pid = fork();
		if (pid == -1)
		{
			perror("fork error");
			exit(EXIT_FAILURE);
		}

		if (pid == 0)
		{
			if ((execvp(line, av)) == -1)
			{
				printf("%s: No such file or directory\n", av[0]);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (waitpid(pid, &status, 0) == -1)
			{
				perror("waitppid error");
				exit(EXIT_FAILURE);
			}
		}
	}

	free(line);
	return (0);
}
