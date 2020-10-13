#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LINE 80 /* The maximum length command */

int main(void) {
	char *args[MAX_LINE/2 + 1]; /* command line arguments */
	char input[MAX_LINE];
	int should_run = 1; /* flag to determine when to exit program */
	int i, j;

	while (should_run) {
		printf("osh>");
		fflush(stdout);
		scanf("%[^\n]%*c", input);
		i = 0;
		args[i] = strtok(input, " ");

		while(args[i] != NULL) {
			i++;
			args[i] = strtok(NULL, " ");
		}

		if(strcmp(args[0], "exit") == 0) {
			break;
		}

		if(strcmp(args[i - 1], "&") != 0) {
			pid_t pid;
			pid = fork();
			if(pid < 0) {
				fprintf(stderr, "Fork Failed\n");
				return 1;
			}else if(pid == 0) {
				execvp(args[0], args);
				for(j = 0; j < i; j++) {
					args[j] = NULL;
				}
			} else {
				wait(NULL);
			}
		} else {
			pid_t pid;
			pid = fork();
			if(pid < 0) {
				fprintf(stderr, "Fork Failed\n");
				return 1;
			} else if(pid == 0) {
				args[i - 1] = NULL;
				execvp(args[0], args);
			} else {
				printf("\n\n");
			}
		}
	}
	return 0;
}