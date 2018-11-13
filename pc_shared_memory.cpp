#include <iostream>
#include<pthread.h>
#include<semaphore.h>

using namespace std;


#define BUFFER_SIZE 10
int buffer[BUFFER_SIZE]; //Buffer to hold the values

pthread_mutex_t mutex;  // Shared memory locking mechanism
sem_t full,empty;

int main()
{
	cout << "Producer consumer problem using shared memory\n";
}
