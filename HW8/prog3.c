#include <stdio.h>
#include <string.h>
 
int main(int argc, char *argv[]) {
	char c;

	int count;
	int i = 0;

	FILE *fp1;
	FILE *fp2;

	if(strcmp(argv[1], "-f") == 0) {
		if(argc < 4) {
			printf("Error! Please specify input and output files\n");
			return 1;
		} else {
			char *filename1 = argv[2];
			char *filename2 = argv[3];

			fp1 = fopen(filename1, "r");
			fp2 = fopen(filename2, "w");

			fseek(fp1,0,SEEK_END);
			count = ftell(fp1);

			while (i < count) {
				i++;
				fseek(fp1,-i,SEEK_END);
				c = fgetc(fp1);
				fputc(c, fp2);
			}

			fclose(fp1);
			fclose(fp2);
		}
	} else if(argc < 2) {
		printf("Error! Please specify input file\n");
		return 1;
	} else {
		char *filename1 = argv[1];

		fp1 = fopen(filename1, "r");

		fseek(fp1,0,SEEK_END);
		count = ftell(fp1);

		while (i < count) {
			i++;
			fseek(fp1,-i,SEEK_END);
			c = fgetc(fp1);
			printf("%c", c);
		}

		fclose(fp1);
	}

	return 0;
}