#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void toString(char *str, int num) {
	int i, rem, len = 0, n;
	n = num;
	while (n != 0) {
		len++;
		n /= 10;
	}

	for (i = 0; i < len; i++) {
		rem = num % 10;
		num = num / 10;
		str[len - (i + 1)] = rem + '0';
	}
	
	str[len] = '\0';
}

int main(int argc, char **argv) {
	char num_str[10];
	int counter = 1;
	int choice = 0;
	int file_desc = 0;
	int l = 0;
	int savedStdout = dup(1);

	if (argc != 2) {
		printf ("Invalid input file name\n");
		return -1;
	}

	file_desc = open(argv[1], O_CREAT | O_WRONLY | O_APPEND, 777);
	
	if(file_desc < 0) {
		printf("Error opening the file\n");
		return 1;
	}

	while (1) {
		char outBuffer[128] = "Index is ";
		scanf(" %c", &choice);
		switch (choice) {
		case 'f':
			l = dup(file_desc);
		
		case 's':
			dup2(l, 1);
			toString (num_str, counter);
			strcat(outBuffer, num_str);
			strcat(outBuffer, "\n");
			counter++;
			write (l, outBuffer, strlen(outBuffer));
			break;

		case 0:
			break;

		default:
			printf("Invalid Choice\n");
		}
	}
	return 0;
}