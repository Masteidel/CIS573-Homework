#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "buffer.h"

int main() {
	key_t key = ftok("shmfile", 45);
	int shmid = shmget(key, sizeof(bufferStruct), 0666 | IPC_CREAT);
	bufferStruct *buffer = (bufferStruct *)shmat(shmid, (void *)0, 0);

	for (int i = 0; i < MAX_SIZE; i++) {
		buffer->content[i] = 0;
	}

	char c;
	while ((c = fgetc(stdin)) == 'p') {
		fflush(stdin);
	}

	return 0;
}