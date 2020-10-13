#define MAX_SIZE 8

typedef struct {
	int in;
	int out;
	int content[MAX_SIZE]; // will hold ASCII codeof characters
} bufferStruct;