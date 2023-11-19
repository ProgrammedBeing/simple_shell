#include "main.h"
/**
 * execute_command - excutes command
 * @command: Command.
 * Return: Return nothing.
 */
void execute_command(char *command)
{
	int status;
	pid_t pid = fork();

	if (pid < 0)
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execlp(command, command, NULL) == -1)
		{
			printf("%s: No such file or directory\n", command);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

/**
 * main- ENtry point.
 *
 * Return: Nothing.
 */
int main(void)
{
	char *command = NULL;
	size_t len = 0;
	ssize_t nread;

	while (1)
	{
		printf("#cisfun$ ");
		nread = getline(&command, &len, stdin);
		if (nread <= 0)
		{
			printf("\n");
			break;
		}
		if (command[nread - 1] == '\n')
			command[nread - 1] = '\0';
		execute_command(command);
	}
	free(command);
	return (0);
}
