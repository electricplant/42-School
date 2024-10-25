#include <stdio.h>       /* standard I/O routines                 */
#include <pthread.h>     /* pthread functions and data structures */
#include <stdlib.h>


void* PrintHello(void* data)
{
	int	*my_data = (int *)data;

	pthread_detach(pthread_self());
	printf("Hello from new thread\n");
	int i = 0;
	while (i < 11)
	{
		printf("%d %d\n",i,  *my_data);
		(*my_data)++;
		i++;
	}
	pthread_exit(NULL);				/* terminate the thread */
}

/* like any C program, program's execution begins in main */
int main(int argc, char* argv[])
{
	int			rc;					/* return value */
	int			t;
	t_thrd		

	t = 11;
	rc = pthread_create(&thread_id, NULL, PrintHello, &t);  
	if(rc)	/* could not create thread */
	{
		printf("\n ERROR: return code from pthread_create is %d \n", rc);
		exit(1);
	}
	printf("Created new thread (%lu)\n", thread_id);
	pthread_join(thread_id, NULL);
	//pthread_exit(NULL);		/* terminate the thread */
}