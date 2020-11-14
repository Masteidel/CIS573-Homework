#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
  
int main(int argc, char **argv) {
	char c;
	FILE *fp1;
	FILE *fp2;
	FILE *fp3;
	
	if(!(strcmp(argv[1], "-s") == 0 || strcmp(argv[1], "-e") == 0)) {
		printf("Error! Usage: you should use either '-s' or '-e' then the file names\n");
		return 1;
	}

	if(argv[2] == NULL) {
		fp1 = fopen("file1.txt", "r");
	} else {
		fp1 = fopen(argv[1], "r");
	}

	if(argv[3] == NULL) {
		fp2 = fopen("file2.txt", "r");
	} else {
		fp2 = fopen(argv[2], "r");
	}

	if(argv[4] == NULL) {
		fp3 = fopen("file3.txt", "w");
	} else {
		fp3 = fopen(argv[3], "w");
	}

	if(strcmp(argv[1], "-s") == 0) {
		
		while ((c = fgetc(fp1)) != EOF) {
			fputc(c, fp3);
		}

		while ((c = fgetc(fp2)) != EOF) {
			fputc(c, fp3);
		}
	} else if(strcmp(argv[1], "-e") == 0) {
		/*
		while ((c = fgetc(fp2)) != EOF) {
			fputc(c, fp3);
		}

		while ((c = fgetc(fp1)) != EOF) {
			fputc(c, fp3);
		}
		*/
	}

	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	/*
	// Open two files to be merged
	char c; 

	if (fp1 == NULL || fp2 == NULL || fp3 == NULL) { 
		puts("Could not open files"); 
		exit(0); 
	} 

	// Copy contents of first file to file3.txt 
	while ((c = fgetc(fp1)) != EOF) 
		fputc(c, fp3); 

	// Copy contents of second file to file3.txt 
	while ((c = fgetc(fp2)) != EOF) 
		fputc(c, fp3); 

	printf("Merged file1.txt and file2.txt into file3.txt"); 

	fclose(fp1); 
	fclose(fp2); 
	fclose(fp3);
	*/ 
	return 0; 
}