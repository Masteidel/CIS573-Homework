#include <stdio.h>

char myToUpper(char someChar) {
	if (someChar >= 'a' && someChar <= 'z') { // convert character to uppercase
		someChar += ('A' - 'a');
	}
	return someChar;
}

int main() {
	int i;
	char line[1000];
	while(fgets(line, 1000, stdin) != NULL) {   // read line by line
		i = 0;
		while (line[i]) {   // go through all characters of lune
			line[i] = myToUpper(line[i]);
			i++;
		}
		printf("%s", line); // print uppercase line
	}
	return 0;
}