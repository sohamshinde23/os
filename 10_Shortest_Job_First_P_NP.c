#include <stdio.h>
#include <stdbool.h>

struct Process {
    int pid;          // Process ID
    int arrivalTime;
    int burstTime;
    int remainingTime; // For preemptive SJF
    int finishTime;
    int turnAroundTime;
    int waitingTime;
    bool isCompleted;
};

// Function for Non-Preemptive SJF
void sjfNonPreemptive(struct Process processes[], int n) {
    int currentTime = 0, completed = 0;

    while (completed < n) {
        int minIndex = -1;
        int minBurstTime = 1e9;

        // Select the process with the smallest burst time that has arrived
        for (int i = 0; i < n; i++) {
            if (!processes[i].isCompleted && processes[i].arrivalTime <= currentTime &&
                processes[i].burstTime < minBurstTime) {
                minBurstTime = processes[i].burstTime;
                minIndex = i;
            }
        }

        if (minIndex == -1) {
            currentTime++;
        } else {
            // Calculate the finish time, turnaround time, and waiting time
            processes[minIndex].finishTime = currentTime + processes[minIndex].burstTime;
            processes[minIndex].turnAroundTime = processes[minIndex].finishTime - processes[minIndex].arrivalTime;
            processes[minIndex].waitingTime = processes[minIndex].turnAroundTime - processes[minIndex].burstTime;
            processes[minIndex].isCompleted = true;

            currentTime = processes[minIndex].finishTime;
            completed++;
        }
    }
}

// Function for Preemptive SJF
void sjfPreemptive(struct Process processes[], int n) {
    int currentTime = 0, completed = 0;
    int minIndex = -1;
    int minRemainingTime = 1e9;

    while (completed < n) {
        minIndex = -1;
        minRemainingTime = 1e9;

        // Select the process with the smallest remaining time that has arrived
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && !processes[i].isCompleted &&
                processes[i].remainingTime < minRemainingTime) {
                minRemainingTime = processes[i].remainingTime;
                minIndex = i;
            }
        }

        if (minIndex != -1) {
            processes[minIndex].remainingTime--;
            currentTime++;

            // If process is completed
            if (processes[minIndex].remainingTime == 0) {
                processes[minIndex].finishTime = currentTime;
                processes[minIndex].turnAroundTime = processes[minIndex].finishTime - processes[minIndex].arrivalTime;
                processes[minIndex].waitingTime = processes[minIndex].turnAroundTime - processes[minIndex].burstTime;
                processes[minIndex].isCompleted = true;
                completed++;
            }
        } else {
            currentTime++;
        }
    }
}

void displayResults(struct Process processes[], int n) {
    printf("PID\tArrival\tBurst\tFinish\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t\t%d\n",
               processes[i].pid,
               processes[i].arrivalTime,
               processes[i].burstTime,
               processes[i].finishTime,
               processes[i].turnAroundTime,
               processes[i].waitingTime);
    }

    float totalTurnAroundTime = 0, totalWaitingTime = 0;
    for (int i = 0; i < n; i++) {
        totalTurnAroundTime += processes[i].turnAroundTime;
        totalWaitingTime += processes[i].waitingTime;
    }

    printf("Average Turnaround Time: %.2f\n", totalTurnAroundTime / n);
    printf("Average Waiting Time: %.2f\n", totalWaitingTime / n);
}

int main() {
    int n, choice;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", processes[i].pid);
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].isCompleted = false;
    }

    printf("Choose Scheduling:\n1. Non-Preemptive SJF\n2. Preemptive SJF\n");
    scanf("%d", &choice);

    if (choice == 1) {
        sjfNonPreemptive(processes, n);
    } else if (choice == 2) {
        sjfPreemptive(processes, n);
    } else {
        printf("Invalid choice!\n");
        return 0;
    }

    displayResults(processes, n);
    return 0;
}


/*
Enter the number of processes: 4
Enter arrival time and burst time for process 1: 0 7
Enter arrival time and burst time for process 2: 2 4
Enter arrival time and burst time for process 3: 4 1
Enter arrival time and burst time for process 4: 5 4
Choose Scheduling:
1. Non-Preemptive SJF
*/


/*
The Process struct defines a single process with various attributes:

pid: Process ID for identification.
arrivalTime: The time when the process arrives in the queue.
burstTime: The total time required for the process to complete.
remainingTime: Used for preemptive SJF to track how much burst time is left.
finishTime: The time when the process finishes execution.
turnAroundTime: The total time from arrival to completion.
waitingTime: Time spent waiting to be executed.
isCompleted: Boolean flag indicating if the process has completed.
2. sjfNonPreemptive Function


Absolutely! Let's go through the code step-by-step to understand how it works, focusing on its logic and structure.

Code Breakdown
1. Struct Definition
c
Copy code
struct Process {
    int pid;          // Process ID
    int arrivalTime;
    int burstTime;
    int remainingTime; // For preemptive SJF
    int finishTime;
    int turnAroundTime;
    int waitingTime;
    bool isCompleted;
};
The Process struct defines a single process with various attributes:

pid: Process ID for identification.
arrivalTime: The time when the process arrives in the queue.
burstTime: The total time required for the process to complete.
remainingTime: Used for preemptive SJF to track how much burst time is left.
finishTime: The time when the process finishes execution.
turnAroundTime: The total time from arrival to completion.
waitingTime: Time spent waiting to be executed.
isCompleted: Boolean flag indicating if the process has completed.
2. sjfNonPreemptive Function
c
Copy code
void sjfNonPreemptive(struct Process processes[], int n)
This function implements Non-Preemptive Shortest Job First (SJF) scheduling. Here’s the breakdown of the algorithm inside this function:

Initialize currentTime and completed:

currentTime keeps track of the current time in the system.
completed counts how many processes have finished execution.
Main Loop:

The loop continues until all processes are completed (completed < n).
Process Selection:

For each time unit, the algorithm searches for the process with the shortest burstTime that has arrived (arrivalTime <= currentTime) and isn’t completed.
If a process meets these conditions, it becomes the candidate for execution.
Execution and Calculation:

If no suitable process is found (minIndex == -1), currentTime increments by 1, simulating an idle period.
If a process is selected (minIndex != -1), it finishes execution without interruption:
finishTime is set to currentTime + burstTime.
turnAroundTime and waitingTime are calculated based on finishTime, arrivalTime, and burstTime.
The selected process is marked as completed and currentTime moves forward.
3. sjfPreemptive Function
This function implements Preemptive SJF (Shortest Remaining Time First - SRTF) scheduling.

Initialize currentTime, completed, and Process Selection Variables:

currentTime tracks time progression.
completed tracks how many processes have finished.
minIndex and minRemainingTime help identify the process with the shortest remaining time.
Process Selection:

For each time unit, the function finds the process with the smallest remainingTime that has arrived and hasn’t completed.
If no process is found, currentTime increments (idle time).
If a process is found, it’s preempted every time a new process with a shorter remainingTime arrives.
Execution and Calculation:

The selected process is executed for 1 time unit, decrementing its remainingTime.
If a process completes (remainingTime == 0), its finishTime, turnAroundTime, and waitingTime are calculated.
The completed counter is incremented, and the process is marked as completed.
4. displayResults Function
This function displays the results, including PID, Arrival Time, Burst Time, Finish Time, Turnaround Time, and Waiting Time for each process. It also calculates and displays the average Turnaround Time and Waiting Time.

Display Table Headers:

Prints headers for each attribute of the process.
Loop Through Processes:

For each process, the function prints all calculated values (PID, Arrival, Burst, Finish, Turnaround, Waiting).
It also accumulates total turnaround and waiting times for calculating averages.
Calculate Averages:

The total turnaround and waiting times are divided by the number of processes to find averages, which are then printed.
5. main Function
The main function serves as the starting point for program execution.

Input Process Details:

The user is prompted to enter the number of processes.
For each process, arrival time and burst time are inputted and stored. remainingTime is initialized to burstTime for preemptive scheduling, and isCompleted is set to false.
Choose Scheduling Algorithm:

The user chooses between Non-Preemptive (1) and Preemptive SJF (2).
Based on the user’s choice, either sjfNonPreemptive or sjfPreemptive is called.
Display Results:

After scheduling, displayResults is called to print each process’s details and average times.
Summary
Non-Preemptive SJF executes the shortest available job without interruption, making it simple but potentially causing long waits for short processes arriving after long processes.
Preemptive SJF (SRTF) allows preemption, giving preference to new processes with shorter remaining times, reducing average waiting time but adding complexity.
*/


// --------------------------------------------------------------------------------
#include <stdio.h>
#include <limits.h>

void find_sjf_np(int n, int bt[], int at[], int ft[], int tat[], int wt[]) {
    int bt_rem[n], done[n], time = 0, min_bt, shortest;
    for (int i = 0; i < n; i++) done[i] = 0;
    for (int i = 0; i < n; i++) bt_rem[i] = bt[i];
    for (int i = 0; i < n; i++) {
        min_bt = INT_MAX;
        shortest = -1;
        for (int j = 0; j < n; j++) {
            if (at[j] <= time && !done[j] && bt_rem[j] < min_bt) {
                min_bt = bt_rem[j];
                shortest = j;
            }
        }
        if (shortest != -1) {
            time += bt_rem[shortest];
            ft[shortest] = time;
            tat[shortest] = ft[shortest] - at[shortest];
            wt[shortest] = tat[shortest] - bt[shortest];
            done[shortest] = 1;
        } else {
            time++;
            i--;
        }
    }
}

void find_sjf_p(int n, int bt[], int at[], int ft[], int tat[], int wt[]) {
    int bt_rem[n], time = 0, shortest = -1, min_bt = INT_MAX, count = 0;
    for (int i = 0; i < n; i++) bt_rem[i] = bt[i];
    while (count < n) {
        min_bt = INT_MAX;
        shortest = -1;
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && bt_rem[i] < min_bt && bt_rem[i] > 0) {
                min_bt = bt_rem[i];
                shortest = i;
            }
        }
        if (shortest != -1) {
            time++;
            bt_rem[shortest]--;
            if (bt_rem[shortest] == 0) {
                count++;
                ft[shortest] = time;
                tat[shortest] = ft[shortest] - at[shortest];
                wt[shortest] = tat[shortest] - bt[shortest];
            }
        } else time++;
    }
}

void print_times(int n, int at[], int bt[], int ft[], int tat[], int wt[]) {
    printf("Process\tArrival Time\tBurst Time\tFinish Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i+1, at[i], bt[i], ft[i], tat[i], wt[i]);
    }
}

int main() {
    int n, bt[20], at[20], ft[20], tat[20], wt[20], choice;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter burst times: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
    }
    printf("Enter arrival times: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &at[i]);
    }

    printf("Choose SJF Scheduling Type:\n");
    printf("1. Non-Preemptive SJF\n");
    printf("2. Preemptive SJF\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        find_sjf_np(n, bt, at, ft, tat, wt);
    } else if (choice == 2) {
        find_sjf_p(n, bt, at, ft, tat, wt);
    } else {
        printf("Invalid choice!\n");
        return 1;
    }

    print_times(n, at, bt, ft, tat, wt);

    return 0;
}

// input
// 3
// 4
// 1
// 5
// 0
// 2
// 3
// 2