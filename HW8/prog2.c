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

	if(argc < 3) {
		printf("Error! Please specify 3 files\n");
		return 1;
	}

	char *filename1 = argv[2];
	char *filename2 = argv[3];
	char *filename3 = argv[4];

	fp1 = fopen(filename1, "r");
	fp2 = fopen(filename2, "r");
	fp3 = fopen(filename3, "w");

	if(strcmp(argv[1], "-s") == 0) {
		
		while ((c = fgetc(fp1)) != EOF) {
			fputc(c, fp3);
		}

		fprintf(fp3, "\n");
		
		while ((c = fgetc(fp2)) != EOF) {
			fputc(c, fp3);
		}
		
	} else if(strcmp(argv[1], "-e") == 0) {
		while ((c = fgetc(fp2)) != EOF) {
			fputc(c, fp3);
		}

		fprintf(fp3, "\n");

		while ((c = fgetc(fp1)) != EOF) {
			fputc(c, fp3);
		}
	}

	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	return 0; 
}