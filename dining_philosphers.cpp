#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h>
#include<iostream>
#include<time.h>
#include <unistd.h>

#define NO_OF_PHILOSOPHERS 5
#define EAT 0
#define THINK 1
#define HUNGRY 2

sem_t mutex_lock;
sem_t semaphore_array[NO_OF_PHILOSOPHERS];
int state[NO_OF_PHILOSOPHERS];
int phil[NO_OF_PHILOSOPHERS] = { 0, 1, 2, 3, 4 }; 


using namespace std;

void check_if_neighbours_eat(int phnum)
{
	int left,right;
	left = (phnum + 4) % NO_OF_PHILOSOPHERS;
	right = (phnum + 1) % NO_OF_PHILOSOPHERS;

	if (state[phnum] == HUNGRY
        && state[left] != EAT
        && state[right] != EAT) {
        // state that eating
        state[phnum] = EAT;
	

	sleep(2);
	cout << "Philosopher " << phnum + 1 << "taking fork" << left + 1 << "and" << phnum + 1 << " and eating\n";
	sem_post(& semaphore_array[phnum]);
	}

}

void take_up_chopsticks(int phnum)
{

    sem_wait(&mutex_lock);

    state[phnum] = HUNGRY;

    cout << "Philosopher " << phnum + 1 << " is hungry\n";
    // eat if neighbours are not eating
    check_if_neighbours_eat(phnum);

    sem_post(&mutex_lock);

    // if unable to eat wait to be signalled
    sem_wait(&semaphore_array[phnum]);

    sleep(1);
}

void put_down_chopsticks(int phnum)
{
	int left,right;
       
	sem_wait(&mutex_lock);

	state[phnum] = THINK;

        cout << "Philosopher " << phnum  + 1 << "thinks\n";

        left = (phnum + 4) % NO_OF_PHILOSOPHERS;
        right = (phnum + 1) % NO_OF_PHILOSOPHERS;

	check_if_neighbours_eat(left);
	check_if_neighbours_eat(right);

        sem_post(&mutex_lock);

}

void* philospher(void * id)
{ 
  
    int i;
    for ( i = 0; i < 3;i ++) { 
  
        int * j = (int *)id; 
  
        sleep(1); 
  
        take_up_chopsticks(*j); 
  
        sleep(0); 
  
        put_down_chopsticks(*j); 
    } 
} 
 

int main()
{

	int i;
	pthread_t thread_id[NO_OF_PHILOSOPHERS];
	cout << "Dining philospher problem\n";
	sem_init(&mutex_lock, 0, 1);

	for (i = 0; i < NO_OF_PHILOSOPHERS; i++)
	{

		sem_init(&semaphore_array[i], 0, 0);
	}

    	for (i = 0; i < NO_OF_PHILOSOPHERS; i++) {

        pthread_create(&thread_id[i], NULL,philospher, &phil[i]);

        printf("Philosopher %d is thinking\n", i + 1);
   	 }

    	for (i = 0; i < NO_OF_PHILOSOPHERS; i++)
	{
        pthread_join(thread_id[i], NULL); 
	}
	return 0;
}
