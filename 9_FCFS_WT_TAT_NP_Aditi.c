#include <stdio.h>

struct Process {
    int pid;       // Process ID
    int arrivalTime;
    int burstTime;
    int finishTime;
    int turnAroundTime;
    int waitingTime;
};

void calculateTimes(struct Process processes[], int n) {
    int currentTime = 0;

    for (int i = 0; i < n; i++) {
        // If the process arrives after the current time, update the current time to the arrival time of the process
        if (currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime;
        }

        // Finish time is the current time plus the burst time
        processes[i].finishTime = currentTime + processes[i].burstTime;

        // Turnaround time is finish time minus arrival time
        processes[i].turnAroundTime = processes[i].finishTime - processes[i].arrivalTime;

        // Waiting time is turnaround time minus burst time
        processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;

        // Update current time to finish time of the current process
        currentTime = processes[i].finishTime;
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
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", processes[i].pid);
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
    }

    // Sort processes by arrival time (FCFS scheduling)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].arrivalTime > processes[j].arrivalTime) {
                struct Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    calculateTimes(processes, n);
    displayResults(processes, n);

    return 0;
}

/*
Enter the number of processes: 3
Enter arrival time and burst time for process 1: 0 4
Enter arrival time and burst time for process 2: 1 3
Enter arrival time and burst time for process 3: 2 2

*/



/*
Process: A program that needs to be executed. Each process has:

Arrival Time: When the process arrives in the system.
Burst Time: How much time the process needs to complete execution.
Finish Time: When the process finishes execution.
Turnaround Time: The total time the process spends from arrival to completion (Finish Time - Arrival Time).
Waiting Time: The time a process spends waiting in the ready queue (Turnaround Time - Burst Time).
FCFS Scheduling: Processes are executed in the order of their arrival. If two processes arrive at the same time, the one listed first in the input will execute first.

This structure (struct Process) stores all the details about a process: its ID (pid), arrival time, burst time, finish time, turnaround time, and waiting time.

2. calculateTimes Function:
This function calculates the finish time, turnaround time, and waiting time for each process.
The current time starts at 0 and keeps increasing as processes finish.
For each process, we check if it arrives after the current time, in which case the current time is updated to the process's arrival time.
The finish time is calculated by adding the burst time to the current time.
Turnaround time is the difference between the finish time and the arrival time.
Waiting time is the difference between turnaround time and burst time.
The current time is updated after each process finishes.
3. displayResults Function:
This function displays the details of all processes and calculates the average turnaround time and waiting time.

It first prints the details for each process (ID, arrival time, burst time, finish time, turnaround time, waiting time).
Then it calculates the total turnaround time and waiting time for all processes.
Finally, it computes and prints the average turnaround time and average waiting time.
4. Main Function:
The main() function is where the program begins execution.

First, it asks for the number of processes (n) from the user.
Then, it creates an array of n processes and asks the user to input the arrival time and burst time for each process.
The processes are sorted by arrival time to implement the First-Come, First-Serve (FCFS) scheduling.
It then calls calculateTimes() to compute the times for each process.
Finally, it calls displayResults() to display the results and compute the averages.
How FCFS Works in This Code:
The processes are sorted based on their arrival time. This ensures that the first process to arrive is the first to execute.
The program calculates the finish time, turnaround time, and waiting time for each process based on the order they are scheduled to execute.
Turnaround time tells you how long a process takes from arrival to completion, and waiting time tells you how much time the process was sitting in the ready queue before it got executed.
*/


//fcfs
#include <stdio.h>

void find_fcfs(int n, int bt[], int at[], int ft[], int tat[], int wt[]) {
    int ct = 0;
    for (int i = 0; i < n; i++) {
        if (ct < at[i])
            ct = at[i];
        ft[i] = ct + bt[i];
        ct = ft[i];
        tat[i] = ft[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }
}

void print_times(int n, int at[], int bt[], int ft[], int tat[], int wt[]) {
    printf("Process\tArrival Time\tBurst Time\tFinish Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i+1, at[i], bt[i], ft[i], tat[i], wt[i]);
    }
}

int main() {
    int n, bt[20], at[20], ft[20], tat[20], wt[20];
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

    find_fcfs(n, bt, at, ft, tat, wt);
    print_times(n, at, bt, ft, tat, wt);

    return 0;
}