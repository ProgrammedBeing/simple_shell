#include "main.h"
#define BUFSIZE 1024

void printPrompt() {
    printf("#cisfun$ ");
}

int main(void) 
{
	pid_t pid;
    char inputBuffer[BUFSIZE];
    int status = 0;

    while (1) {
        printPrompt();

        if (fgets(inputBuffer, BUFSIZE, stdin) == NULL) {
            if (feof(stdin)) {
                printf("\n");
                break; 
            } else {
                perror("Input error");
                exit(EXIT_FAILURE);
            }
        }

        inputBuffer[strcspn(inputBuffer, "\n")] = '\0';

        pid = fork();
        if (pid == -1) {
            perror("fork error");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            if (execlp(inputBuffer, inputBuffer, NULL) == -1) {
                perror("Command execution error");
                exit(EXIT_FAILURE);
            }
        } else {
            wait(&status);
        }
    }

    return status;
}
