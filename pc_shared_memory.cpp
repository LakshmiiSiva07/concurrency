#include <iostream>
#include<pthread.h>
#include <semaphore.h>

using namespace std;


#define BUFFER_SIZE 10
int buffer[BUFFER_SIZE]; //Buffer to hold the values
int index = 0;

pthread_mutex_t mutex;  // Shared memory locking mechanism
sem_t full,empty;

// Producer function
void *producer( void * thread_num)
{
	int thread_number = *(int *)thread_num;
        sem_wait(&full); // Wait if the buffer is full
	pthread_mutex_lock(&mutex);
        int produced_value = rand()%1000; // Random value produced
        buffer[index++] = produced_value;
	cout << "Produced by thread" << thread_number << ",\t item" << produced_value;
	pthread_mutex_unlock(&mutex);
	sem_post(&empty);
	pthread_exit(0);

}

//Consumer function
void *consumer( void * thread_num)
{
	 int thread_number = *(int *)thread_num;
	 sem_wait(&empty);
	 pthread_mutex_lock(&mutex);
	 int consumed_value;
	 consumed_value =  buffer[--index];
	 cout << "Consumed by thread" << thread_number << ",\t item" << consumed_value;
         pthread_mutex_unlock(&mutex);
         sem_post(&full);
         pthread_exit(0);
}


int main()
{

	cout << "Producer consumer problem using shared memory\n";
	// Intializing lock and semaphores
	sem_init(&empty,0,0);
	sem_init(&full,0,BUFFER_SIZE);
	pthread_mutex_init(&mutex,NULL);
}
