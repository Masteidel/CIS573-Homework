#include <stdio.h>
#include <string.h>

#define MAX_NUM_OF_ARGS 5
#define MAX_ARG_SIZE 256

int main(int argc, char *argv[]) {
	char argumentArray[MAX_NUM_OF_ARGS][MAX_ARG_SIZE];
	int counter;
	for(counter = 0; counter < MAX_NUM_OF_ARGS; counter++) {
		strcpy(argumentArray[counter], "defaultArg");
	}

	if(argc > MAX_NUM_OF_ARGS) {
		printf("Usage : %s Arg1 Arg2 ... \n", argv[0]);
		printf("\t Your arguments exceeded the maximum of arguments (%d) \n", MAX_NUM_OF_ARGS - 1);
		return 1;
	}

	for(counter = 0; counter < argc; counter++) {
		strcpy(argumentArray[counter], argv[counter]);
	}

	for(counter = 0; counter < MAX_NUM_OF_ARGS; counter++) {
		printf("argumentArray[%d]: %s \n", counter, argumentArray[counter]);
	}

	return 0;
}