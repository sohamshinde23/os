#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define N 5

sem_t forks[N];

void *philosopher(void *arg) {
    int id = *((int *)arg);


    for (int i = 0; i < 3; i++) {
        printf("Philosopher %d is thinking.\n", id);
        usleep(100000);


        sem_wait(&forks[id]);
        sem_wait(&forks[(id + 1) % N]);


        printf("Philosopher %d is eating.\n", id);
        usleep(100000);


        sem_post(&forks[id]);
        sem_post(&forks[(id + 1) % N]);


        printf("Philosopher %d finished eating.\n", id);
        usleep(100000);
    }
    return NULL;
}


int main() {
    pthread_t philosophers[N];
    int ids[N];


    for (int i = 0; i < N; i++)
        sem_init(&forks[i], 0, 1);


    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }


    for (int i = 0; i < N; i++)
        pthread_join(philosophers[i], NULL);


    for (int i = 0; i < N; i++)
        sem_destroy(&forks[i]);


    return 0;
}


/*
pthread.h: Provides the functionality to create and manage threads.
semaphore.h: Provides the functionality to use semaphores for synchronization.
stdio.h: Standard I/O functions like printf().
unistd.h: Provides access to the POSIX operating system API (for usleep() to simulate delay).
2. Defining Constants:

3. Declaring Semaphores for Forks:
An array forks[] of semaphores is defined. Each philosopher requires two forks to eat. 
Each semaphore represents a fork that a philosopher can pick up or put down

The philosopher function is the entry point for each philosopher (each thread).
The id of the philosopher is passed as an argument to the thread function. Each philosopher has a unique ID (from 0 to 4 in this case).

5. Thinking and Eating Loop:
Each philosopher will think, eat, and then finish eating for a total of 3 times.
Thinking: The philosopher spends time thinking (simulated using usleep(100000)).
Eating: The philosopher needs two forks to eat:
The left fork is forks[id].
The right fork is forks[(id + 1) % N]. The % N ensures that for philosopher 4, the right fork is forks[0], forming a circular table.
Synchronization:
sem_wait(&forks[id]) and sem_wait(&forks[(id + 1) % N]) ensure the philosopher waits for both forks before eating.
sem_post(&forks[id]) and sem_post(&forks[(id + 1) % N]) are used to release the forks after eating, allowing other philosophers to pick them up.
Eating Time: Simulated with another usleep(100000) to represent the time taken by a philosopher to eat.
6. Main Function:

he philosophers[] array holds the thread IDs for each philosopher.
The ids[] array stores the unique ID for each philosopher.
The loop sem_init(&forks[i], 0, 1) initializes each semaphore (forks[i]) to 1, meaning each fork is initially available.

7. Creating Threads (Philosophers):

For each philosopher, a new thread is created using pthread_create().
Each philosopher is assigned an ID (from 0 to 4).
The philosopher function is passed as the thread function, and the philosopher's ID is passed as an argument.
8. Joining Threads:
The pthread_join() function is used to wait for each philosopher's thread to finish before the program exits.
This ensures that the main program waits for all philosophers to finish their work (thinking and eating).
9. Destroying Semaphores:
After all philosophers have finished, the semaphores are destroyed using sem_destroy(), which cleans up the semaphore resources.
Understanding Synchronization with Semaphores:
The semaphores control access to the forks. Each fork is a shared resource between two philosophers.
sem_wait() blocks the philosopher if the fork is already taken, ensuring that only one philosopher can use a fork at a time.
sem_post() releases the fork, allowing another philosopher to use it.
Deadlock Prevention:
There is still a risk of deadlock in this simple model: if every philosopher picks up the left fork at the same time, they will all wait for the right fork, resulting in a deadlock.
One way to avoid deadlock would be to implement a strategy where one philosopher (say philosopher 0) picks up the forks in reverse order (right first), but this code does not address that specifically.

*/