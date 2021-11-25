#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<math.h>

#define NUMTHREADS 4

int SharedVariable = 0;
pthread_mutex_t lock;
pthread_barrier_t barr;

void *SimpleThread(void *arg){
	int threadId = *((int*)arg);
	int i;

	for(i=0; i < 20; i++){
	#ifdef PTHREAD_SYNC
	pthread_mutex_lock(&lock);
	#endif
	
	printf("thread %d sees values %d\n", threadId, SharedVariable);
	SharedVariable++;

	#ifdef PTHREAD_SYNC
	pthread_mutex_unlock(&lock);
	#endif
	}
	pthread_barrier_wait(&barr);
	printf("Thread %d sees final value %d\n", threadId, SharedVariable);
	return NULL;
}

int main()
{

int i,err;
int x;

/*if(argc < 2){
	printf("Usage: threadWithSync  number\n");
	exit(1);
}

x = atoi(argv[1]);*/

//spawn threads 
pthread_t threads[NUMTHREADS];
int threadIds[NUMTHREADS] = {0};

//initializing mutex
pthread_mutex_init(&lock,NULL);
//intializing barrier
pthread_barrier_init(&barr, NULL, NUMTHREADS);

for(i = 0; i < NUMTHREADS; i++){
	threadIds[i]= i;
	//create threads
	err = pthread_create(&threads[i],NULL, SimpleThread, (void*)&threadIds[i]);
	if(err){
		printf("ERROR creating THREADS, return code %d\n",err);
		exit(-1);
	}
}

//wait for threads to finish
for(i = 0; i < NUMTHREADS;i++){
pthread_join(threads[i],NULL);
}

return 0;
}
