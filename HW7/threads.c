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
} buffer_t; 

buffer_t buffer;

void producer(buffer_t *b) {
	pthread_mutex_lock(&b->mutex);

	while (b->occupied >= MAX_SIZE) {
		pthread_cond_wait(&b->less, &b->mutex);
	}

	assert(b->occupied < MAX_SIZE);

	b->content[b->in++] = 1+rand() % 100;

	b->in %= MAX_SIZE;
	b->occupied++;

	pthread_cond_signal(&b->more);

	pthread_mutex_unlock(&b->mutex);
}

int consumer(buffer_t *b) {
	int item;
	pthread_mutex_lock(&b->mutex);
	while(b->occupied <= 0) {
		pthread_cond_wait(&b->more, &b->mutex);
	}

	assert(b->occupied > 0);

	item = b->content[b->out++];
	b->out %= MAX_SIZE;
	b->occupied--;

	pthread_cond_signal(&b->less);
	pthread_mutex_unlock(&b->mutex);

	return(item);
}

int main(int argc, char **argv, char **envp) {
	int numItems;
	int i;
	key_t key = ftok("shmfile", 45);
	int shmid = shmget(key, sizeof(buffer_t), 0666 | IPC_CREAT);
	buffer_t *buffer = (buffer_t *)shmat(shmid, (void *)0, 0);
	buffer->in = -1;
	buffer->out = 0;

	for(i = 0; i < MAX_SIZE; i++) {
		buffer->content[i] = 0;
	}

	printf("Enter number of items to be produced: ");
	scanf("%d", &numItems);

	for(i = 0; i < numItems; i++) {
		producer(buffer);
	}

	for(i = numItems; i > 0; i--) {
		consumer(buffer);
	}

	return 0;
}