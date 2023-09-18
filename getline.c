#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *line = 0;
	size_t len = 0;

	printf("$ ");
	getline(&line, &len, stdin);
	printf("%s\n", line);
	free (line);
}
