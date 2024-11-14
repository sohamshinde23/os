#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void create_zombie_process() {
    pid_t pid = fork();

    if (pid > 0) {
        // Parent process creates a zombie
        printf("Parent process (PID: %d) created a zombie process (PID: %d)\n", getpid(), pid);
        sleep(1); // Reduced sleep time to 1 second to minimize wait time for zombie
    } else if (pid == 0) {
        // Child process exits to become a zombie
        printf("Child process (PID: %d) exiting to become a zombie\n", getpid());
        exit(0);
    } else {
        perror("Fork failed for zombie process");
    }
}

void create_orphan_process() {
    pid_t pid = fork();

    if (pid > 0) {
        // Parent exits to make the child an orphan
        printf("Parent process (PID: %d) exiting, creating an orphan process\n", getpid());
        exit(0);
    } else if (pid == 0) {
        // Child process becomes orphaned and adopted by init (PID 1)
        sleep(1); // Keep child alive briefly to show orphan behavior
        printf("Orphan child process (PID: %d) now adopted by init process (PPID: %d)\n", getpid(), getppid());
    } else {
        perror("Fork failed for orphan process");
    }
}

void calculate_even_odd_sum(int arr[], int n) {
    pid_t pid = fork();

    if (pid > 0) {
        // Parent calculates sum of even numbers
        int even_sum = 0;
        for (int i = 0; i < n; i++) {
            if (arr[i] % 2 == 0) {
                even_sum += arr[i];
            }
        }
        wait(NULL); // Wait for child process to finish
        printf("Parent process (PID: %d) - Sum of even numbers: %d\n", getpid(), even_sum);
    } else if (pid == 0) {
        // Child calculates sum of odd numbers
        int odd_sum = 0;
        for (int i = 0; i < n; i++) {
            if (arr[i] % 2 != 0) {
                odd_sum += arr[i];
            }
        }
        printf("Child process (PID: %d) - Sum of odd numbers: %d\n", getpid(), odd_sum);
        exit(0); // Exit child process after completing calculation
    } else {
        perror("Fork failed for even-odd sum calculation");
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // Hardcoded array
    int n = sizeof(arr) / sizeof(arr[0]);

    // Task 1: Create a zombie process
    create_zombie_process();
    sleep(1); // Reduced sleep time to 1 second to observe zombie process briefly

    // Task 2: Create an orphan process
    create_orphan_process();
    sleep(1); // Reduced sleep time to 1 second to observe orphan process briefly

    // Task 3: Calculate sum of even and odd numbers using parent and child process
    calculate_even_odd_sum(arr, n);

    return 0;
}

/*
Certainly! Let's go through the entire code step by step so that you can understand the logic behind it.

### Code Overview:

This C program demonstrates three concepts:
1. **Zombie Process**: A process that has completed execution but still has an entry in the process table because its parent hasn't yet read its exit status.
2. **Orphan Process**: A process whose parent has terminated, so it is adopted by the `init` process (PID 1).
3. **Sum Calculation**: The parent calculates the sum of even numbers from an array, while the child calculates the sum of odd numbers.

### Code Breakdown:

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
```

- **`#include <stdio.h>`**: Includes the standard I/O library for using functions like `printf()`.
- **`#include <stdlib.h>`**: Includes the standard library for functions like `exit()` and `malloc()`.
- **`#include <sys/types.h>`**: Includes the system types needed for system calls, such as `pid_t` for process IDs.
- **`#include <sys/wait.h>`**: Includes functions for waiting for child processes, such as `wait()`.
- **`#include <unistd.h>`**: Includes functions for process control, such as `fork()`, `getpid()`, and `getppid()`.

### Functions Explained:

#### 1. `create_zombie_process()`

This function creates a zombie process:

```c
void create_zombie_process() {
    pid_t pid = fork();  // Create a child process
```

- **`pid_t pid = fork();`**: The `fork()` system call is used to create a new process. This will return:
  - A **positive value** (child's PID) to the parent process.
  - `0` to the child process.
  - `-1` if the `fork()` fails.

```c
    if (pid > 0) {
        // Parent process creates a zombie
        printf("Parent process (PID: %d) created a zombie process (PID: %d)\n", getpid(), pid);
        sleep(1);  // Sleep for 1 second to keep the child as a zombie briefly
    } else if (pid == 0) {
        // Child process exits to become a zombie
        printf("Child process (PID: %d) exiting to become a zombie\n", getpid());
        exit(0);  // Child exits immediately, becoming a zombie
    } else {
        perror("Fork failed for zombie process");
    }
}
```

- **Parent Process** (`pid > 0`):
  - The parent prints a message showing it created a child (which will become a zombie).
  - The parent calls `sleep(1)` to wait for 1 second, allowing the child to become a zombie.
  
- **Child Process** (`pid == 0`):
  - The child prints a message and immediately exits with `exit(0)`.
  - Since the parent hasn't yet called `wait()` to collect the child’s exit status, the child remains in the **zombie** state for a short period.

#### 2. `create_orphan_process()`

This function demonstrates the creation of an orphan process:

```c
void create_orphan_process() {
    pid_t pid = fork();  // Create a child process
```

- **`pid_t pid = fork();`**: Again, this creates a child process, returning the process ID (PID) for the parent and `0` for the child.

```c
    if (pid > 0) {
        // Parent exits to make the child an orphan
        printf("Parent process (PID: %d) exiting, creating an orphan process\n", getpid());
        exit(0);  // Parent exits, making the child an orphan
    } else if (pid == 0) {
        // Child process becomes orphaned and adopted by init (PID 1)
        sleep(1);  // Sleep for 1 second to show orphan behavior
        printf("Orphan child process (PID: %d) now adopted by init process (PPID: %d)\n", getpid(), getppid());
    } else {
        perror("Fork failed for orphan process");
    }
}
```

- **Parent Process** (`pid > 0`):
  - The parent exits immediately using `exit(0)`, causing the child to become an **orphan**. The orphaned child will be adopted by the `init` process (with PID 1).

- **Child Process** (`pid == 0`):
  - The child sleeps for 1 second to simulate the orphaned state, and then prints that it has been adopted by `init` (i.e., its new parent is `init` with PID 1).

#### 3. `calculate_even_odd_sum(int arr[], int n)`

This function calculates the sum of even and odd numbers in an array using the parent and child processes:

```c
void calculate_even_odd_sum(int arr[], int n) {
    pid_t pid = fork();  // Create a child process
```

- **`pid_t pid = fork();`**: The `fork()` creates a child process that will handle calculating the sum of odd numbers, while the parent calculates the sum of even numbers.

```c
    if (pid > 0) {
        // Parent calculates sum of even numbers
        int even_sum = 0;
        for (int i = 0; i < n; i++) {
            if (arr[i] % 2 == 0) {
                even_sum += arr[i];
            }
        }
        wait(NULL);  // Wait for child process to finish
        printf("Parent process (PID: %d) - Sum of even numbers: %d\n", getpid(), even_sum);
    } else if (pid == 0) {
        // Child calculates sum of odd numbers
        int odd_sum = 0;
        for (int i = 0; i < n; i++) {
            if (arr[i] % 2 != 0) {
                odd_sum += arr[i];
            }
        }
        printf("Child process (PID: %d) - Sum of odd numbers: %d\n", getpid(), odd_sum);
        exit(0);  // Exit the child process after completing its task
    } else {
        perror("Fork failed for even-odd sum calculation");
    }
}
```

- **Parent Process** (`pid > 0`):
  - The parent calculates the sum of even numbers by iterating through the array. It uses `wait(NULL)` to ensure that it waits for the child to complete its task before printing the sum of even numbers.

- **Child Process** (`pid == 0`):
  - The child calculates the sum of odd numbers and prints the result. After finishing the calculation, the child exits using `exit(0)`.

### `main()` Function:

The `main()` function is where the program executes and calls the functions to demonstrate the behaviors:

```c
int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // Hardcoded array of numbers
    int n = sizeof(arr) / sizeof(arr[0]);  // Get the size of the array

    // Task 1: Create a zombie process
    create_zombie_process();
    sleep(1); // Sleep briefly to observe the zombie process

    // Task 2: Create an orphan process
    create_orphan_process();
    sleep(1); // Sleep briefly to observe the orphan process

    // Task 3: Calculate sum of even and odd numbers using parent and child process
    calculate_even_odd_sum(arr, n);

    return 0;
}
```

- **Array**: An array of numbers `{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}` is used.
- **Size Calculation**: `n = sizeof(arr) / sizeof(arr[0])` calculates the number of elements in the array.
- **Function Calls**: The three functions (`create_zombie_process()`, `create_orphan_process()`, and `calculate_even_odd_sum()`) are called sequentially.

### Expected Output:
For the array `{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}`, the output should be something like this:

```text
Parent process (PID: 1234) created a zombie process (PID: 1235)
Child process (PID: 1235) exiting to become a zombie
Orphan child process (PID: 1235) now adopted by init process (PPID: 1)
Parent process (PID: 1234) - Sum of even numbers: 30
Child process (PID: 1235) - Sum of odd numbers: 25
```

### Summary:

- **Zombie Process**: A child process that terminates but remains in the process table until the parent reads its exit status.
- **Orphan Process**: A child process whose parent terminates. It is adopted by the `init` process.
- **Even/Odd Sum Calculation**: The parent calculates the sum of even numbers, and the child calculates the sum of odd numbers from the array.

Let me know if you need more details or further clarification!
*/