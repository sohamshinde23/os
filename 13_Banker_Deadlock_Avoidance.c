#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

void print_matrices(int processes, int resources, int max[][MAX_RESOURCES], int allot[][MAX_RESOURCES], int need[][MAX_RESOURCES]) {
    printf("\nAllocation Matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            printf("%d ", allot[i][j]);
        }
        printf("\n");
    }

    printf("\nMax Matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            printf("%d ", max[i][j]);
        }
        printf("\n");
    }

    printf("\nNeed Matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
}


bool is_safe(int processes, int resources, int avail[], int max[][MAX_RESOURCES], int allot[][MAX_RESOURCES]) {

    int work[MAX_RESOURCES], finish[MAX_PROCESSES] = {0}, safe_seq[MAX_PROCESSES];
    int need[MAX_PROCESSES][MAX_RESOURCES];

    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            need[i][j] = max[i][j] - allot[i][j];
        }
    }

      print_matrices(processes, resources, max, allot, need);

    for (int i = 0; i < resources; i++) {
        work[i] = avail[i];
    }

    int count = 0;

    while (count < processes) {
        bool found = false;
        for (int p = 0; p < processes; p++) {
            if (finish[p] == 0) {
                int j;
                for (j = 0; j < resources; j++) {
                    if (need[p][j] > work[j]) {
                        break;
                    }
                }
                if (j == resources) {
                    for (int k = 0; k < resources; k++) {
                        work[k] += allot[p][k];
                    }
                    finish[p] = 1;
                    safe_seq[count++] = p;
                    found = true;
                }
            }
        }
        if (!found) {
            printf("System is not in a safe state.\n");
            return false;
        }
    }
    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < processes; i++) {
        printf("%d ", safe_seq[i]);
    }

    printf("\n");

    return true;

}

int main() {
    int processes, resources;
    printf("Enter the number of processes: ");
    scanf("%d", &processes);

    printf("Enter the number of resources: ");
    scanf("%d", &resources);

    int avail[MAX_RESOURCES];
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int allot[MAX_PROCESSES][MAX_RESOURCES];

    printf("Enter the available resources: \n");
    for (int i = 0; i < resources; i++) {
        scanf("%d", &avail[i]);
    }

    printf("Enter the maximum matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &allot[i][j]);
        }
    }
    is_safe(processes, resources, avail, max, allot);
    return 0;

}


// input
// 5
// 4
// 1 5 2 0
// 0 0 1 2
// 1 7 5 0
// 2 3 5 6
// 0 6 5 2
// 0 6 5 6
// 0 0 1 2
// 1 0 0 0
// 1 3 5 4
// 0 6 3 2
// 0 0 14


/*

This program implements the Banker's Algorithm for deadlock avoidance. The algorithm checks if the system is in a "safe state" or not, based on the available resources and the current allocation of resources to various processes. Here's a step-by-step explanation of the code, breaking it down into easy-to-understand parts:
Key Concepts:
Processes: The individual tasks that need resources.
Resources: The limited resources that are needed by processes to complete.
Max Matrix: Represents the maximum resources each process may need.
Allocation Matrix: Represents the current resources allocated to each process.
Need Matrix: Represents the remaining resources each process needs to finish.
Code Explanation:
1. Input Section:
The program first asks the user for:
The number of processes (processes).
The number of resources (resources).
The available resources (avail[]).
The maximum resources required by each process (max[][]).
The current resource allocation for each process (allot[][]).
2. Print Matrices:
The function print_matrices() is called to display:

The Allocation Matrix: The resources currently held by each process.
The Max Matrix: The maximum resources that each process may need.
The Need Matrix: The remaining resources needed by each process, calculated as Need = Max - Allocation.
This function helps the user visualize the system's current state, though it's mainly for debugging purposes here.

3. Safety Check (Banker's Algorithm):
The main logic to determine if the system is in a safe state is implemented in the function is_safe(). Here's how it works:

Need Matrix Calculation: For each process, the Need matrix is calculated as the difference between the Max matrix and the Allocation matrix (i.e., Need[i][j] = Max[i][j] - Allot[i][j]).

Work Array: The work[] array represents the number of available resources at any given time. Initially, this is set to the available resources.

Finish Array: The finish[] array keeps track of whether a process has finished executing or not. Initially, all processes are unfinished.

Safe Sequence Check:

The algorithm tries to find a process that can be completed. A process can be completed if for all its remaining resource needs (from the Need matrix), the available resources (in the work array) are sufficient.
If a process can finish:
The available resources are increased by the resources currently held by that process (since the process has finished, it releases those resources).
The process is marked as finished (finish[i] = 1), and its index is added to the safe sequence.
If no process can be finished in a round (i.e., no process can meet its resource needs), it means the system is not in a safe state and deadlock might occur.
Output:

If all processes can eventually finish (i.e., if a safe sequence is found), the system is in a safe state and the safe sequence is printed.
If no safe sequence can be found, the system is in a deadlock state and the program prints "System is not in a safe state."
4. Main Function:
The program takes input from the user, stores it in the appropriate arrays (avail[], max[][], and allot[][]), and then calls is_safe() to check if the system is in a safe state.
*/