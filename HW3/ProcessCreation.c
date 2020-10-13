#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
	printf("%d *\n", getpid());
	fork();
	printf("%d **\n", getpid());
	fork();
	printf("%d ***\n", getpid());
	fork();
	printf("%d ****\n", getpid());
	fork();
	printf("%d *****\n", getpid());
	fork();
	printf("%d ******\n", getpid());
	sleep(10);
	return EXIT_SUCCESS;
}