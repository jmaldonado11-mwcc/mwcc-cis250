#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LINE 256
void run_test(char *args[], int *total, int *passed);
int display_test(char *args[], int status)
{
	
	if(WIFEXITED(status) && WEXITSTATUS(status) == 0)
	{
		printf("%s: passed\n" , args[0]);
		return 1;
	}else
	{
		printf("%s:failed\n", args [0]);
		return 0;
	}
}
void display_summary(int total, int pass)
{
	printf("=======================\n");
	printf(" TEST SUMMARY\n");
	printf("Tests executed:	%d\n", total);
	printf("Tests Passed:	%d\n", pass);
	printf("Tests Failed:   %d\n", total - pass);
}

int main()
{
	FILE *test_file;
	char line[MAX_LINE];

	int test_total = 0;
	int test_pass = 0;

	test_file = fopen("tests.txt" , "r");

	if(test_file == NULL)
	{
		perror("Unable to open tests");
		return 1;
	}

	while(fgets(line, sizeof(line), test_file) != NULL)
	{
		char *pos = strchr(line , '\n');
		if(pos)
		{
			*pos = '\0';
		}

		if (line[0] == '\0' || line[0] == '#' || line[0] == '\r')
		{
			continue;
		}

		char *args[MAX_LINE];
		int i = 0;

		char *toks = strtok(line, " ");

		while(toks != NULL && i < MAX_LINE - 1)
		{
			args[i++] = toks;
			toks = strtok(NULL, " ");
		}

		args[i] = NULL;

		if (args[0] == NULL)
		{
			continue;
		}
		run_test(args, &test_total, &test_pass);
	}
	fclose(test_file);

	display_summary(test_total, test_pass);

	return 0;
}

void run_test(char *args[], int *total, int *pass)
{
	if(args == NULL || args[0] == NULL)
	{
		printf("no args\n");
	}
	pid_t pid = fork();

	if(pid < 0)
	{
		perror("fork");
	}
	else if(pid == 0)
	{
		execvp(args[0], args);
		perror("Exec failed");
		exit(1);
	}
	else
	{
		int status;
		wait(&status);
		if(WIFEXITED(status))
		{
			printf("Done waiting with %d\n", WIFEXITED(status));
		}
		(*total)++;
		*pass += display_test(args,status);
	}
}
