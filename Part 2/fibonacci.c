#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int n; //size of fibonacci sequence
int *fibseq; //array holds value of each fibonacci element
int i; //count for threads

void *runn(void *arg);

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
	 printf("Format is: ./a.out <IntegerValue>\n");
	 return -1;
	}//validate num of arguments

	if(atoi(argv[1]) < 0)
	{
	 printf("%d must be >= 0\n", atoi(argv[1]));
	 return -1;
	}

	n = atoi(argv[1]);
	fibseq = (int *)malloc(n * sizeof(int));
	pthread_t *threads = (pthread_t *)malloc(n*sizeof(pthread_t));

	pthread_attr_t attr; //set of thread attribute
	pthread_attr_init(&attr);

	for(i = 0; i < n; i++)
	{
	 pthread_create(&threads[i], &attr, runn, NULL);
	}//end of creating threads
	
	int j;
	for(j=0; j < n; j++)
	{
	 pthread_join(threads[j],NULL);
	}//end of waiting threads to exit

	//printing fibseq
	printf("The Fibonacci sequence: ");
	int k;

	for(k = 0; k < n-1; k++)
	{
	 printf("%d,", fibseq[k]);
	}
	printf("%d\n",fibseq[n-1]);
	return 0;
	
}//end of main

void *runn(void *arg)
{
	if(i==0)
	{
	 fibseq[i] = 0;
	 pthread_exit(0);
	}//first fib element

	if(i==1)
	{
	 fibseq[i]=1;
	 pthread_exit(0);
	} //second fib element
	else
	{
	 fibseq[0] = 0;
	 fibseq[1] = 1;

	 int p, pp, fibp, fibpp;
	
	 p = (i-1);
	 pp = (i-2);
	 fibp = fibseq[p];
	 fibpp = fibseq[pp];
	 fibseq[i] = fibseq[i-1] + fibseq[i-2];
	 pthread_exit(0); //thread exit
	}
}
