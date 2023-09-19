#include "shell.h"

int execute_command(char *tokens[])
{
    struct stat command_stat;

    if (stat(tokens[0], &command_stat) == 0)
    {
        pid_t pid = fork();

        if (pid < 0)
        {
            perror("fork");
            return (-1);
        }
        else if (pid == 0)
        {
            if (execve(tokens[0], tokens, NULL) == -1)
            {
                perror("execve");
                return (-1);
            }
        }
        else
        {
            int status;

            if (wait(&status) == -1)
            {
                perror("wait");
                return (-1);
            }
        }
    }
    else
    {
        return (-1);
    }
    return (0);
}
