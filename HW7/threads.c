#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <sys/shm.h>

#define MAX_SIZE 8

typedef struct {
	int content[MAX_SIZE];
	int occupied;
	int in;
	int out;
	pthread_mutex_t mutex;
	pthread_cond_t more;
	pthread_cond_t less;
}
buffer_t; 

buffer_t buffer;

void producer(buffer_t *b, int item) {
	pthread_mutex_lock(&b->mutex);

	while (b->occupied >= MAX_SIZE)
		pthread_cond_wait(&b->less, &b->mutex);

	assert(b->occupied < MAX_SIZE);

	b->content[b->in++] = item;

	b->in %= MAX_SIZE;
	b->occupied++;

	/* now: either b->occupied < BSIZE and b->nextin is the index
	   of the next empty slot in the buffer, or
	   b->occupied == BSIZE and b->nextin is the index of the
	   next (occupied) slot that will be emptied by a consumer
	   (such as b->nextin == b->nextout) */

	pthread_cond_signal(&b->more);

	pthread_mutex_unlock(&b->mutex);
}

int consumer(buffer_t *b) {
	int item;
	pthread_mutex_lock(&b->mutex);
	while(b->occupied <= 0)
		pthread_cond_wait(&b->more, &b->mutex);

	assert(b->occupied > 0);

	item = b->content[b->out++];
	b->out %= MAX_SIZE;
	b->occupied--;

	pthread_cond_signal(&b->less);
	pthread_mutex_unlock(&b->mutex);

	return(item);
}

int main(int argc, char **argv, char **envp) {
	char cmd;
	key_t key = ftok("shmfile", 45);
	int shmid = shmget(key, sizeof(buffer_t), 0666 | IPC_CREAT);
	buffer_t *buffer = (buffer_t *)shmat(shmid, (void *)0, 0);
	buffer->in = -1;
	buffer->out = 0;

	for(int i = 0; i < MAX_SIZE; i++) {
		buffer->content[i] = 0;
	}

	while(1) {
		scanf("%c", &cmd);
		if(cmd == 'p') {
			if (buffer->content[(buffer->in + 1) % MAX_SIZE]) {
				printf("<Buffer is full>\n");
			} else {
				buffer->in = (buffer->in + 1) % MAX_SIZE;
				buffer->content[buffer->in] = 1+rand() % 100;
			}

			for (int i = buffer->out; i != buffer->in; i = (i + 1) % MAX_SIZE){
				printf("%d ", buffer->content[i]);
			}
			printf("\n");
			continue;

		} else if(cmd == 'c') {
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
			}
			printf("\n");

		} else if(cmd == '0') {
			break;

		} else {
			continue;
		}
	}

	return 0;
}