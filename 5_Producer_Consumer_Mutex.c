#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5  

int buffer[BUFFER_SIZE];
int in = 0;  
int out = 0; 
int item_count = 0; // Tracks the number of items in the buffer

pthread_mutex_t mutex;      
pthread_cond_t not_full;    
pthread_cond_t not_empty;   

void* producer(void* arg);
void* consumer(void* arg);
void add_to_buffer(int item);
int remove_from_buffer();
void show_menu();
int is_buffer_full();
int is_buffer_empty();

int producer_count = 1;
int consumer_count = 1;

int main() {
    pthread_t p_thread, c_thread;
    int choice, item;

    pthread_mutex_init(&mutex, NULL);      
    pthread_cond_init(&not_full, NULL);    
    pthread_cond_init(&not_empty, NULL);   

    while (1) {
        show_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:  
                if (is_buffer_full()) {
                    printf("Buffer is full! Cannot produce more items.\n");
                    break;
                }
                printf("Enter the item to produce: ");
                scanf("%d", &item);

                // Allocate memory for the item
                int* item_ptr = malloc(sizeof(int));
                *item_ptr = item;

                pthread_create(&p_thread, NULL, producer, item_ptr);
                pthread_join(p_thread, NULL);
                producer_count++;  
                break;

            case 2:  
                if (is_buffer_empty()) {
                    printf("Buffer is empty! Nothing to consume.\n");
                    break;
                }
                pthread_create(&c_thread, NULL, consumer, NULL);
                pthread_join(c_thread, NULL);
                consumer_count++;  
                break;

            case 3:  
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice, try again.\n");
        }
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&not_full);
    pthread_cond_destroy(&not_empty);

    return 0;
}

void* producer(void* arg) {
    int item = *(int*)arg; // Dereference the pointer to get the item
    free(arg); // Free the allocated memory

    printf("Producer %d is trying to produce an item...\n", producer_count);

    pthread_mutex_lock(&mutex);
    while (is_buffer_full()) {
        pthread_cond_wait(&not_full, &mutex); // Wait until buffer is not full
    }

    printf("Producer %d is adding item to buffer...\n", producer_count);
    add_to_buffer(item);  
    printf("Produced item by Producer %d: %d\n", producer_count, item);
    printf("Current buffer items: %d\n", item_count);

    pthread_cond_signal(&not_empty); // Signal that the buffer is not empty
    pthread_mutex_unlock(&mutex);

    printf("Producer %d has left the buffer.\n", producer_count);
    return NULL;
}

void* consumer(void* arg) {
    int item;

    printf("Consumer %d is trying to consume an item...\n", consumer_count);

    pthread_mutex_lock(&mutex);
    while (is_buffer_empty()) {
        pthread_cond_wait(&not_empty, &mutex); // Wait until buffer is not empty
    }

    printf("Consumer %d is removing item from buffer...\n", consumer_count);
    item = remove_from_buffer();  
    printf("Consumed item by Consumer %d: %d\n", consumer_count, item);
    printf("Current buffer items: %d\n", item_count);

    pthread_cond_signal(&not_full); // Signal that the buffer is not full
    pthread_mutex_unlock(&mutex);

    printf("Consumer %d has left the buffer.\n", consumer_count);
    return NULL;
}

void add_to_buffer(int item) {
    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;  
    item_count++; // Increment item count when adding an item
}

int remove_from_buffer() {
    int item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;  
    item_count--; // Decrement item count when removing an item
    return item;
}

void show_menu() {
    printf("\n----Producer-Consumer Menu----\n");
    printf("1. Produce an item\n");
    printf("2. Consume an item\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
}

int is_buffer_full() {
    return item_count == BUFFER_SIZE; // Buffer is full if item_count equals BUFFER_SIZE
}

int is_buffer_empty() {
    return item_count == 0; // Buffer is empty if item_count is 0
}

/*
1
10
2
10
*/

/*
Here’s a detailed explanation of each part of the code, function by function:

### **Global Variables and Initialization**
1. **`buffer[BUFFER_SIZE]`**:
   - A shared array (or buffer) of size `BUFFER_SIZE` (which is 5 in this case). This is used to hold the items that are produced and consumed by the producer and consumer threads.

2. **`in`, `out`, `item_count`**:
   - `in`: This is the index where the next item produced will be placed in the buffer.
   - `out`: This is the index from where the next item will be consumed from the buffer.
   - `item_count`: This tracks the current number of items in the buffer. It is used to determine if the buffer is full or empty.

3. **`pthread_mutex_t mutex`**:
   - This is a mutex (mutual exclusion) lock that ensures that only one thread (either producer or consumer) can access the shared buffer at a time. It is used to protect the critical section of the code where the buffer is modified.

4. **`pthread_cond_t not_full`, `pthread_cond_t not_empty`**:
   - These are condition variables used for synchronization. 
   - `not_full`: This condition variable is used to signal the producer when the buffer is not full and it can safely add an item to the buffer.
   - `not_empty`: This condition variable is used to signal the consumer when the buffer is not empty and it can safely consume an item.

### **`main` Function**
The `main` function is responsible for managing the user interaction, creating threads, and invoking the producer and consumer threads based on the user’s menu choices. It performs the following tasks:

1. **Initialize mutex and condition variables** using `pthread_mutex_init()` and `pthread_cond_init()` before starting the threads.
2. **User input loop**:
   - The user is prompted to select from a menu with three options: producing an item, consuming an item, or exiting.
   - If the user chooses to produce, the program checks if the buffer is full. If it is not full, it creates a producer thread, passes the item to produce, and waits for the thread to finish.
   - If the user chooses to consume, the program checks if the buffer is empty. If it is not empty, it creates a consumer thread and waits for the thread to finish.
   - The program keeps looping until the user chooses to exit (`choice 3`).

3. **Cleanup**:
   - After exiting the loop, the program calls `pthread_mutex_destroy()` and `pthread_cond_destroy()` to clean up the mutex and condition variables before exiting the program.

### **`producer` Function**
The `producer` function is executed by the producer thread. It performs the following tasks:

1. **Acquire the mutex** using `pthread_mutex_lock()`. This prevents any other thread (consumer) from modifying the buffer while the producer is working on it.
   
2. **Check if the buffer is full** using `is_buffer_full()`:
   - If the buffer is full, the producer will wait for the `not_full` condition variable to be signaled, indicating that space is available in the buffer.
   - The producer waits by calling `pthread_cond_wait(&not_full, &mutex)`, which releases the mutex temporarily and waits for a signal (when the buffer is no longer full).

3. **Produce the item**:
   - Once the buffer is not full, the producer adds the item to the buffer by calling `add_to_buffer()`. The `in` index is updated, and `item_count` is incremented to reflect the new item in the buffer.

4. **Signal the consumer** using `pthread_cond_signal(&not_empty)`. This signals the consumer thread that the buffer is no longer empty, and it can now consume an item.

5. **Release the mutex** using `pthread_mutex_unlock()` to allow other threads to access the buffer.

6. **Output the current state**:
   - The producer prints messages indicating the item produced and the current number of items in the buffer.

7. **Free the allocated memory** for the item pointer at the end of the function to prevent memory leaks.

### **`consumer` Function**
The `consumer` function is executed by the consumer thread. It performs the following tasks:

1. **Acquire the mutex** using `pthread_mutex_lock()`. This ensures mutual exclusion when accessing the shared buffer.

2. **Check if the buffer is empty** using `is_buffer_empty()`:
   - If the buffer is empty, the consumer waits for the `not_empty` condition variable to be signaled, indicating that there is an item available in the buffer.
   - The consumer waits by calling `pthread_cond_wait(&not_empty, &mutex)`, which releases the mutex temporarily and waits for a signal (when the buffer is no longer empty).

3. **Consume the item**:
   - Once the buffer is not empty, the consumer removes an item from the buffer by calling `remove_from_buffer()`. The `out` index is updated, and `item_count` is decremented to reflect the item that was removed.

4. **Signal the producer** using `pthread_cond_signal(&not_full)`. This signals the producer thread that space is available in the buffer for producing more items.

5. **Release the mutex** using `pthread_mutex_unlock()` to allow other threads to access the buffer.

6. **Output the current state**:
   - The consumer prints messages indicating the item consumed and the current number of items in the buffer.

### **Buffer Management Functions**
1. **`add_to_buffer(int item)`**:
   - This function is responsible for adding an item to the buffer.
   - It places the item in the position indicated by `in`, then updates `in` to the next position, wrapping around to the beginning of the buffer when the end is reached (`in = (in + 1) % BUFFER_SIZE`).
   - The `item_count` is incremented to reflect the new item in the buffer.

2. **`remove_from_buffer()`**:
   - This function is responsible for removing an item from the buffer.
   - It retrieves the item from the position indicated by `out`, then updates `out` to the next position, wrapping around to the beginning of the buffer when the end is reached (`out = (out + 1) % BUFFER_SIZE`).
   - The `item_count` is decremented to reflect the removal of an item.

### **Utility Functions**
1. **`show_menu()`**:
   - This function displays the menu to the user, offering three choices: produce an item, consume an item, or exit the program.

2. **`is_buffer_full()`**:
   - This function checks if the buffer is full by comparing `item_count` with `BUFFER_SIZE`. If `item_count` equals `BUFFER_SIZE`, the buffer is full, and the function returns `1` (true).

3. **`is_buffer_empty()`**:
   - This function checks if the buffer is empty by checking if `item_count` is `0`. If the buffer is empty, the function returns `1` (true).

### **Summary of Thread Synchronization**
- **Producer-Consumer Problem**: This program implements the classical producer-consumer problem using **threads**, **mutex** for mutual exclusion, and **condition variables** (`not_full` and `not_empty`) for synchronization between the producer and consumer.
- **Mutex** ensures that only one thread (either producer or consumer) can access the shared buffer at a time.
- **Condition variables** are used to signal the producer when the buffer has space, and to signal the consumer when there is an item to consume.

### **Thread Management**
- The program creates threads using `pthread_create()` for both producers and consumers. After each thread finishes its work, the main thread waits for them to finish using `pthread_join()` before proceeding with the next operation.

This program is a practical implementation of **thread synchronization** in a multi-threaded environment and ensures that the buffer operates correctly without conflicts or race conditions between the producer and consumer threads.
*/