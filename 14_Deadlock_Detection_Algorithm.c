#include <stdio.h>
#include <stdbool.h>

void deadlockDetection(int available[], int max[][10], int allocation[][10], int processes, int resources) {
    int work[resources];
    bool finish[processes];
    
    for (int i = 0; i < resources; i++)
        work[i] = available[i];
    
    for (int i = 0; i < processes; i++)
        finish[i] = false;
    
    bool done;
    do {
        done = false;
        for (int i = 0; i < processes; i++) {
            if (!finish[i]) { 
                bool canProceed = true;
                for (int j = 0; j < resources; j++) {
                    if (max[i][j] - allocation[i][j] > work[j]) {
                        canProceed = false;
                        break;
                    }
                }
                if (canProceed) {
                    for (int k = 0; k < resources; k++)
                        work[k] += allocation[i][k];
                    finish[i] = true;
                    done = true;
                }
            }
        }
    } while (done);

    bool deadlock = false;
    printf("Processes in deadlock: ");
    for (int i = 0; i < processes; i++) {
        if (!finish[i]) {
            printf("P%d ", i);
            deadlock = true;
        }
    }
    if (!deadlock)
        printf("None");
    printf("\n");
}

int main() {
    int processes, resources;
    
    printf("Enter the number of processes: ");
    scanf("%d", &processes);
    printf("Enter the number of resources: ");
    scanf("%d", &resources);

    int available[resources];
    int max[processes][10];
    int allocation[processes][10];

    printf("Enter available resources:\n");
    for (int i = 0; i < resources; i++) {
        printf("Resource %d: ", i + 1);
        scanf("%d", &available[i]);
    }

    printf("Enter maximum resource demand for each process:\n");
    for (int i = 0; i < processes; i++) {
        printf("Process P%d:\n", i);
        for (int j = 0; j < resources; j++) {
            printf("Resource %d: ", j + 1);
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter allocated resources for each process:\n");
    for (int i = 0; i < processes; i++) {
        printf("Process P%d:\n", i);
        for (int j = 0; j < resources; j++) {
            printf("Resource %d: ", j + 1);
            scanf("%d", &allocation[i][j]);
        }
    }

    deadlockDetection(available, max, allocation, processes, resources);
    
    return 0;
}

/*
5
4
1 5 2 0
0 0 1 2
1 7 5 0
2 3 5 6
0 6 5 2
0 6 5 6
0 0 1 2
1 0 0 0
1 3 5 4
0 6 3 2
0 0 1 4
*/


/*
The code implements **deadlock detection** in an operating system by using the **Banker’s Algorithm**. Here’s a detailed explanation of how the code works:

### Code Structure and Purpose
1. **Headers and Definitions**:
   - `#include <stdio.h>` and `#include <stdbool.h>`: We include standard input/output and Boolean libraries for basic functionality.
   - We define the `deadlockDetection` function to check if there are any processes in deadlock.

2. **Function: `deadlockDetection`**
   - **Inputs**:
     - `available[]`: An array representing the number of available instances of each resource type.
     - `max[][]`: A matrix representing the maximum demand of each resource for each process.
     - `allocation[][]`: A matrix showing the number of resources of each type currently allocated to each process.
     - `processes` and `resources`: The number of processes and resource types, respectively.

   - **Variables**:
     - `work[]`: An array to represent the currently available resources that can be used by processes.
     - `finish[]`: A Boolean array to track whether each process has completed or not.
     - `done`: A flag to track whether any process was completed in the last pass through the processes.

   - **Initialization**:
     - Copies the `available` resources into `work[]`, which represents the resources available at any point during execution.
     - Sets all elements in `finish[]` to `false`, indicating that no process has initially completed.

   - **Main Loop**:
     - The algorithm runs in a `do-while` loop, which will continue as long as any process is marked as completed (`done` is `true`).
     - In each iteration, it checks if there is a process that:
       - Has not yet finished (`finish[i] == false`).
       - Has a demand (`max[i][j] - allocation[i][j]`) that can be satisfied with the currently available resources (`work[j]`).

     - **Process Selection**:
       - If a process can proceed (i.e., its demand is less than or equal to `work`), we add its allocated resources back to `work[]`, marking it as complete (`finish[i] = true`), and set `done = true`.
       - If no process can proceed, it increments the `time` by 1 unit (used here to simulate waiting).

   - **Deadlock Detection**:
     - After the `do-while` loop, any process with `finish[i] == false` is in deadlock.
     - The code then prints out any process that has not finished, indicating it is in a deadlock. If all processes are finished (`finish[i] == true` for all `i`), it prints "None," indicating no deadlock.

3. **Function: `main`**
   - **Inputs**:
     - Prompts the user to enter the number of processes and resources.
     - Requests available resources and constructs the `available[]` array.
     - Requests each process’s maximum resource demand and stores it in `max[][]`.
     - Requests each process’s current allocated resources and stores them in `allocation[][]`.

   - **Calling Deadlock Detection**:
     - Calls the `deadlockDetection` function with the provided inputs.
     - Prints out any processes detected to be in deadlock.

### Example Execution
Given the input provided, the program checks if any processes are in deadlock. If a process cannot acquire enough resources to proceed, the algorithm will eventually determine that it is stuck and label it as in deadlock.

### Key Points
1. **Safety Check**: This code is similar to the safety check in the Banker’s Algorithm, where it checks if processes can finish with the currently available resources.
2. **Deadlock Detection**: Instead of trying to prevent deadlock, the code only detects it. Processes that cannot get the resources they need (i.e., `finish[i] == false`) are considered deadlocked.
3. **Efficient Resource Utilization**: Processes that finish release their resources to `work[]`, allowing other processes to potentially complete.

This code is designed to handle resource allocation and check for deadlocks in a simple way, focusing on finding a solution in cases where multiple processes compete for limited resources.
*/