#include <math.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "buffer.h"

int main() {
	key_t key = ftok("shmfile", 45);
	int shmid = shmget(key, sizeof(bufferStruct), 0666 | IPC_CREAT);
	bufferStruct *buffer = (bufferStruct *)shmat(shmid, (void *)0, 0);
	
	char c;
	while ((c = fgetc(stdin)) == '\n') {
		fflush(stdin);

		if (buffer->content[buffer->out] == 0) {
			buffer->in = -1;
			buffer->out = 0;
			printf("Buffer is empty...\n");
			continue;
		}

		printf("%d consumed\n", buffer->content[buffer->out]);
		buffer->content[buffer->out] = 0;
		buffer->out = (buffer->out + 1) % MAX_SIZE;

		if (buffer->content[buffer->out] == 0) {
			continue;
		}

		for (int i = buffer->out; i != buffer->in; i = (i + 1) % MAX_SIZE) {
			printf("%d ", buffer->content[i]);
			printf("%d\n", buffer->content[i]);
		}
	}

	return 0;
}