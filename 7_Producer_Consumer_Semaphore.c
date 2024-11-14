#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5  // Reduced buffer size for quicker full/empty demonstration

int buffer[BUFFER_SIZE];  // Shared buffer
int count = 0;            // Counter for items in the buffer

pthread_mutex_t mutex;  // Mutex for critical section

// Function to display the buffer's current state
void displayBuffer() {
    printf("Buffer: [ ");
    for (int i = 0; i < BUFFER_SIZE; i++) {
        if (i < count)
            printf("%d ", buffer[i]);
        else
            printf("- ");  // Empty slot
    }
    printf("] ");
    
    if (count == 0) {
        printf("(Buffer is empty)\n");
    } else if (count == BUFFER_SIZE) {
        printf("(Buffer is full)\n");
    } else {
        printf("\n");
    }
}

// Producer function
void* producer(void* arg) {
    while (1) {
        int item = rand() % 100;  // Produce a random item

        pthread_mutex_lock(&mutex);  // Wait to access the buffer

        // Wait if buffer is full (busy-waiting approach)
        while (count == BUFFER_SIZE) {
            pthread_mutex_unlock(&mutex);
            usleep(100); // Sleep a bit to avoid busy-waiting too aggressively
            pthread_mutex_lock(&mutex);
        }

        buffer[count] = item;  // Produce item into buffer
        count++;
        printf("Producer produced: %d\n", item);
        displayBuffer();  // Display buffer state

        pthread_mutex_unlock(&mutex);  // Release buffer

        usleep(rand() % 2000);  // Simulate production time
    }
}

// Consumer function
void* consumer(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);  // Wait to access the buffer

        // Wait if buffer is empty (busy-waiting approach)
        while (count == 0) {
            pthread_mutex_unlock(&mutex);
            usleep(100); // Sleep a bit to avoid busy-waiting too aggressively
            pthread_mutex_lock(&mutex);
        }

        int item = buffer[--count];  // Consume item from buffer
        printf("Consumer consumed: %d\n", item);
        displayBuffer();  // Display buffer state

        pthread_mutex_unlock(&mutex);  // Release buffer

        usleep(rand() % 2000);  // Simulate consumption time
    }
}

int main() {
    pthread_t prod_thread, cons_thread;

    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // Wait for threads to finish (optional, typically runs indefinitely)
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // Clean up
    pthread_mutex_destroy(&mutex);

    return 0;
}



/*

Sure! Let's go through the code step by step to explain how it works. You can use this explanation in your lab examination.

Overview:
This program is a Producer-Consumer problem implementation, which demonstrates synchronization between two types of threads (producers and consumers) operating on a shared buffer. The goal is to ensure that producers add items to the buffer when there is space, and consumers remove items from the buffer when it is not empty. The threads synchronize their actions using mutexes (for mutual exclusion) and busy-waiting.

Key Concepts:
Producer Thread: A thread that produces an item and places it in a shared buffer.
Consumer Thread: A thread that consumes an item by removing it from the shared buffer.
Shared Buffer: An array that stores the items. It has a fixed size, and its state is managed using a count variable.
Mutex (Mutual Exclusion): Used to ensure that only one thread can access the shared buffer at any given time. This prevents race conditions.
Busy-Waiting: Instead of using semaphores or condition variables, this approach uses loops and sleeps to wait for the buffer to be in a valid state (full or empty).
Explanation by Sections:
Global Variables:

buffer[BUFFER_SIZE]: An array representing the shared buffer. It can hold a fixed number of items (in this case, BUFFER_SIZE = 5).
count: Keeps track of how many items are currently in the buffer.
mutex: A mutex (or lock) that is used to protect the buffer from concurrent access by multiple threads.
Function: displayBuffer():

This function is used to print the current state of the buffer.
It loops through the buffer, printing the items that have been produced and placing a - symbol in the empty slots.
After displaying the buffer, it also prints whether the buffer is empty or full based on the count.
Producer Function (producer()):

The producer is an infinite loop that continuously produces items.
A random item is generated using rand() % 100 to simulate the production of different items.
Mutex Locking: The producer locks the mutex using pthread_mutex_lock(&mutex) to ensure that no other thread (consumer or producer) can access the shared buffer during this time.
Busy-Waiting for Full Buffer: If the buffer is full (i.e., count == BUFFER_SIZE), the producer releases the mutex (pthread_mutex_unlock(&mutex)) and sleeps for a short time (usleep(100)), allowing other threads (consumer) to access the buffer. Once the buffer has space again, the producer re-acquires the mutex and proceeds to add an item to the buffer.
Item Production: After ensuring there's space in the buffer, the producer adds the item to the buffer (buffer[count] = item) and increments the count to reflect the new number of items in the buffer.
After producing the item, the producer prints the produced item and the current state of the buffer, then releases the mutex with pthread_mutex_unlock(&mutex).
The producer thread then sleeps for a random period (usleep(rand() % 2000)) to simulate the time it takes to produce an item.
Consumer Function (consumer()):

The consumer is also an infinite loop, which continuously consumes items from the buffer.
Mutex Locking: The consumer locks the mutex at the beginning to ensure exclusive access to the buffer.
Busy-Waiting for Empty Buffer: If the buffer is empty (count == 0), the consumer releases the mutex and sleeps for a short time (usleep(100)), allowing the producer to add items. Once the buffer is not empty, the consumer re-acquires the mutex and continues.
Item Consumption: After ensuring that the buffer is not empty, the consumer removes an item from the buffer (int item = buffer[--count]) and prints the consumed item.
After consuming the item, the consumer prints the current state of the buffer and releases the mutex with pthread_mutex_unlock(&mutex).
The consumer then sleeps for a random period (usleep(rand() % 2000)) to simulate the time it takes to consume an item.
Main Function (main()):

The main() function is where the threads are created and initialized.
Mutex Initialization: The mutex (pthread_mutex_init(&mutex, NULL)) is initialized to protect the shared buffer.
Thread Creation:
Three producer threads are created: Thread producer1, Thread producer2, Thread producer3.
Two consumer threads are created: Thread consumer1, Thread consumer2.
Thread Execution: Each of the threads is started using the pthread_create() function. The producer and consumer threads will run in parallel, each following their respective logic for producing and consuming items.
Thread Joining: The pthread_join() calls are used to wait for the producer and consumer threads to finish their execution (although they run indefinitely in this case).
Mutex Destruction: Once the threads finish, the mutex is destroyed using pthread_mutex_destroy(&mutex) to clean up.
Key Synchronization Concepts:
Mutex for Critical Section: The mutex ensures that only one thread (either a producer or a consumer) can access the shared buffer at a time. This prevents concurrent modification of the buffer, which could lead to race conditions.

Busy-Waiting: In this version, the producer and consumer check the buffer's state (count) and actively wait if the buffer is full or empty. They release the mutex when they are waiting and re-lock it when the condition changes. This simple synchronization method avoids complex semaphores and is often used for small-scale, simple concurrency problems.

Execution Flow:
The producer threads continuously produce items and add them to the buffer, while the consumer threads consume the items.
When the buffer is full, the producer waits by releasing the mutex and sleeping. Similarly, when the buffer is empty, the consumer waits.
The buffer's state is displayed after each action (production or consumption), showing the items in the buffer and whether it is full or empty.
*/