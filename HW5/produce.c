#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "buffer.h"

int main() {
	key_t key = ftok("shmfile", 45);
	int shmid = shmget(key, sizeof(bufferStruct), 0666 | IPC_CREAT);
	bufferStruct *buffer = (bufferStruct *)shmat(shmid, (void *)0, 0);
	buffer->in = -1;
	buffer->out = 0;

	for (int i = 0; i < MAX_SIZE; i++) {
		buffer->content[i] = 0;
	}

	char c;
	while ((c = fgetc(stdin)) == '\n') {
		fflush(stdin);

		if (buffer->content[(buffer->in + 1) % MAX_SIZE]) {
			printf("<Buffer is full>\n");
			continue;
		}

		buffer->in = (buffer->in + 1) % MAX_SIZE;
		buffer->content[buffer->in] = 1+rand() % 100;

		for (int i = buffer->out; i != buffer->in; i = (i + 1) % MAX_SIZE){
			printf("%d ", buffer->content[i]);
			printf("%d\n", buffer->content[i]);
		}
	}
	
	return 0;
}