#include <stdio.h>
#include <unistd.h>

/**
 * main - PID
 *
 * Return: Always 0.
 */
int main(void)
{
	pid_t my_pid;
	pid_t my_ppid;

	my_pid = getpid();
	my_ppid = getppid();
	write("%u\n", my_pid);
	write("%u\n", my_ppid);
	return (0);
}
