#include "shell.h"

extern char **environ;
/**
 * execute_command - excutes command
 * @command: Command.
 * @av: argument vector
 * Return: Return nothing.
 */
void execute_command(char *command, char **av)
{
	int status;
	pid_t pid = fork();
	char **envVariables = environ;

	if (pid < 0)
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(command, av, envVariables) == -1)
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
 * @argc: Number of arguments
 * @av: argument vector
 * Return: Nothing.
 */
int main(int argc, char **av)
{
	char *command = NULL;
	size_t len = 0;
	ssize_t nread;

	(void)argc;

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
		execute_command(command, av);
	}
	free(command);
	return (0);
}
