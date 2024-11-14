#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex;      
sem_t writeLock;  
int readers = 0;  
int data = 0;     

void* reader(void* arg);
void* writer(void* arg);
void enter_reader(int reader_id);
void exit_reader(int reader_id);
void enter_writer(int writer_id);
void exit_writer(int writer_id);

int main() {
    pthread_t r_threads[5], w_threads[3];

    sem_init(&mutex, 0, 1);
    sem_init(&writeLock, 0, 1);

    for (int i = 0; i < 5; i++) {
        pthread_create(&r_threads[i], NULL, reader, (void*)(size_t)(i+1));
    }

    for (int i = 0; i < 3; i++) {
        pthread_create(&w_threads[i], NULL, writer, (void*)(size_t)(i+1));
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(r_threads[i], NULL);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(w_threads[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&writeLock);

    return 0;
}

void* reader(void* arg) {
    int reader_id = (int)(size_t)arg;
    sleep(rand() % 5); 
    enter_reader(reader_id);
    
    printf("Reader %d: Reading data: %d\n", reader_id, data);
    
    exit_reader(reader_id);
    return NULL;
}

void* writer(void* arg) {
    int writer_id = (int)(size_t)arg;
    sleep(rand() % 5); 
    enter_writer(writer_id);

    data = rand() % 100;  
    printf("Writer %d: Writing data: %d\n", writer_id, data);
    
    exit_writer(writer_id);
    return NULL;
}

void enter_reader(int reader_id) {
    sem_wait(&mutex);  
    readers++;
    if (readers == 1) {
        sem_wait(&writeLock);
    }
    printf("Reader %d is entering the critical section.\n", reader_id);
    sem_post(&mutex);  
}

void exit_reader(int reader_id) {
    sem_wait(&mutex); 
    printf("Reader %d is exiting the critical section.\n", reader_id);
    readers--;
    if (readers == 0) {

        sem_post(&writeLock);
    }
    sem_post(&mutex);  
}

void enter_writer(int writer_id) {
    sem_wait(&writeLock); 
    printf("Writer %d is entering the critical section.\n", writer_id);
}

void exit_writer(int writer_id) {
    printf("Writer %d is exiting the critical section.\n", writer_id);
    sem_post(&writeLock);  
}



/*
his code implements a Readers-Writers problem using semaphores to manage concurrent access to a shared resource (data). The problem involves multiple reader threads and writer threads accessing the shared data, with the following rules:

Readers can access the data concurrently (i.e., multiple readers can read the data at the same time).
Writers require exclusive access to the data (i.e., no readers or other writers can access the data while a writer is writing).
The implementation uses two semaphores (mutex and writeLock) to synchronize access to the shared resource.

Key Concepts:
Semaphores:

mutex: This semaphore is used to manage access to the readers counter, which tracks how many readers are currently accessing the data. It ensures that only one thread (reader or writer) modifies the readers counter at a time.
writeLock: This semaphore ensures that only one writer can access the data at a time and prevents readers from accessing the data while a writer is writing. It is locked when a writer enters and unlocked when the writer exits.
Readers-Writers Problem:

Readers can read the shared data concurrently, but writers need exclusive access to the data, meaning no other readers or writers can access the data during the write operation.
The program follows a strategy known as "first reader blocks writer". The first reader blocks writers by acquiring the writeLock, and the last reader releases the writeLock.
Code Breakdown:
Main Function:
Thread Creation:

The program creates 5 reader threads and 3 writer threads using pthread_create.
Each reader and writer thread is executed by the reader and writer functions respectively.
Thread Joining:

After all threads are created, pthread_join is used to wait for each reader and writer thread to finish before the program terminates.
Semaphore Initialization/Destruction:

sem_init(&mutex, 0, 1) initializes mutex to allow only one thread to modify the readers count at a time.
sem_init(&writeLock, 0, 1) initializes writeLock to allow only one thread (either a writer or the first reader) to access the critical section at a time.
After all threads are done, sem_destroy cleans up the semaphores.
Reader Function:
Random Delay:

Each reader thread waits for a random period before trying to enter the critical section using sleep(rand() % 5). This simulates real-world variability in thread scheduling.
Enter Reader (enter_reader):

The reader first locks the mutex to increment the readers counter safely.
If this is the first reader (i.e., readers == 1), it locks writeLock to prevent writers from entering the critical section.
After the check and potentially locking the writeLock, the reader prints that it is entering the critical section.
The mutex is unlocked, and the reader can proceed to read the data.
Exit Reader (exit_reader):

After finishing reading, the reader locks mutex again to safely decrement the readers counter.
If this is the last reader (i.e., readers == 0), it releases the writeLock, allowing any waiting writers to enter.
The reader then prints that it is exiting the critical section and unlocks mutex.
Writer Function:
Random Delay:

Each writer thread waits for a random period before trying to enter the critical section using sleep(rand() % 5).
Enter Writer (enter_writer):

The writer locks the writeLock semaphore. This ensures exclusive access to the data, so no readers or other writers can access the critical section.
The writer then prints that it is entering the critical section.
Exit Writer (exit_writer):

After writing the data, the writer prints that it is exiting the critical section.
It then releases the writeLock semaphore, allowing other writers or the first reader to enter the critical section.
Data and Synchronization:
Data: The shared variable data represents the resource that readers and writers are accessing. Writers modify this data by setting it to a random value, while readers print the current value of data.

Synchronization:

The use of mutex ensures that changes to the readers count are atomic.
The use of writeLock ensures that when a writer is writing, no readers can access the data and no other writers can write.
The first reader locks the writeLock semaphore to block writers, and the last reader releases it to allow writers to write.
*/