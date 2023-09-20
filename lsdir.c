#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void printPathDirectories()
{
    char *path = getenv("PATH");

    if (path == NULL)
    {
        write(STDERR_FILENO, "PATH environment variable not found.\n", 37);
        return;
    }

    char *token;
    token = strtok(path, ":");
    while (token != NULL)
    {
        write(STDOUT_FILENO, token, strlen(token));
        write(STDOUT_FILENO, "\n", 1);
        token = strtok(NULL, ":");
    }
}

int main(void)
{
    printPathDirectories();
    return 0;
}

