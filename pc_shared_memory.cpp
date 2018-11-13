#include <iostream>
#include<pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;


#define BUFFER_SIZE 10
int buffer[BUFFER_SIZE]; //Buffer to hold the values
int index = 0;

pthread_mutex_t mutex;  // Shared memory locking mechanism
sem_t full,empty;

#define NUM_OF_THREADS 100

// Producer function
void *producer(void * arg)
{

        sem_wait(&full); // Wait if the buffer is full
	pthread_mutex_lock(&mutex);
        int produced_value = rand()%1000; // Random value produced
        buffer[index++] = produced_value;
	cout << "Producer thread item " << produced_value << "\n";
	pthread_mutex_unlock(&mutex);
	sem_post(&empty);
	pthread_exit(0);
        
}

//Consumer function
void *consumer(void * arg)
{

	 sem_wait(&empty);
	 pthread_mutex_lock(&mutex);
	 int consumed_value;
	 consumed_value =  buffer[--index];
	 cout << "Consumed thread item " << consumed_value << "\n";
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
    
	pthread_t producer1[NUM_OF_THREADS],consumer1[NUM_OF_THREADS];
	for ( int k = 0 ; k < NUM_OF_THREADS; k++)
	{	
	int choice = rand() % 2;
        pthread_create(&consumer1[k],NULL,consumer,NULL);
	pthread_create(&producer1[k],NULL,producer,NULL);
	}
	pthread_exit(NULL);
}
