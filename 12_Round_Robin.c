//round-robin
#include <stdio.h>

void find_rr(int n, int bt[], int at[], int ft[], int tat[], int wt[], int quantum) {
    int bt_rem[n], time = 0, count = 0;
    for (int i = 0; i < n; i++) bt_rem[i] = bt[i];
    while (count < n) {
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && bt_rem[i] > 0) {
                if (bt_rem[i] > quantum) {
                    time += quantum;
                    bt_rem[i] -= quantum;
                } else {
                    time += bt_rem[i];
                    bt_rem[i] = 0;
                    ft[i] = time;
                    tat[i] = ft[i] - at[i];
                    wt[i] = tat[i] - bt[i];
                    count++;
                }
            }
        }
    }
}

void print_times(int n, int at[], int bt[], int ft[], int tat[], int wt[]) {
    printf("Process\tArrival Time\tBurst Time\tFinish Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i+1, at[i], bt[i], ft[i], tat[i], wt[i]);
    }
}

int main() {
    int n, bt[20], at[20], ft[20], tat[20], wt[20], quantum;
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
    printf("Enter time quantum for Round Robin: ");
    scanf("%d", &quantum);

    find_rr(n, bt, at, ft, tat, wt, quantum);
    print_times(n, at, bt, ft, tat, wt);

    return 0;
}

/*
Enter number of processes: 3
Enter burst times: 10 5 8
Enter arrival times: 0 1 2
Enter time quantum for Round Robin: 3
*/

/*
This function performs the Round Robin scheduling calculations for each process. It takes in the following parameters:

n: The number of processes.
bt[]: An array of burst times for each process.
at[]: An array of arrival times for each process.
ft[]: An array to store the finish times for each process.
tat[]: An array to store the turnaround times for each process.
wt[]: An array to store the waiting times for each process.
quantum: The time quantum, or maximum time each process can execute in one cycle before being switched out.

bt_rem[]: An array to track the remaining burst time for each process, initialized with each process's original burst time (bt[]).
time: Tracks the current time in the system, initialized to 0.
count: Counts the number of processes that have completed.
Main Scheduling Loop
The while loop runs until all processes have completed (count < n).
Inside, a for loop iterates over each process. For each process, it checks:
Arrival Time Condition (at[i] <= time): The process must have arrived by the current time.
Remaining Burst Time Condition (bt_rem[i] > 0): The process should still have some burst time left.
Executing Each Process
If bt_rem[i] > quantum: The process executes for the full quantum time.
time is increased by quantum, simulating the process's execution.
bt_rem[i] is decreased by quantum, reducing the remaining burst time.
If bt_rem[i] <= quantum: The process completes within the remaining time.
time is increased by the remaining burst time (bt_rem[i]).
bt_rem[i] is set to 0, indicating that the process has completed.
ft[i] is set to the current time, marking the process's finish time.
tat[i] is calculated as the difference between finish time and arrival time.
wt[i] is calculated as the difference between turnaround time and burst time.
count is incremented, marking the process as completed.
2. print_times Function
This function displays the calculated times (arrival, burst, finish, turnaround, and waiting times) for each process. The parameters are:

n: Number of processes.
at[]: Array of arrival times.
bt[]: Array of burst times.
ft[]: Array of finish times.
tat[]: Array of turnaround times.
wt[]: Array of waiting times.
Function Execution

The function prints a table header.
Then, it iterates over each process and displays its times, formatted in a table.
3. main Function
The main function gathers user inputs, calls the find_rr function to calculate scheduling times, and finally calls print_times to display the results.

Input Process Details:
Prompts the user to enter the number of processes (n).
Input Burst and Arrival Times:
The user is prompted to input burst times and arrival times for each process. These values are stored in bt[] and at[].
Input Quantum:
The user specifies the time quantum, which is the maximum time each process can execute in one cycle.
Function Calls:
Calls find_rr to perform the Round Robin scheduling calculations.
Calls print_times to display the results for each process, including finish, turnaround, and waiting times.
Summary
Round Robin Scheduling: Each process is executed in a cyclic order for a maximum of quantum time. If a process's remaining burst time is greater than quantum, it goes back into the queue after quantum time and waits for its next turn. Otherwise, it completes.
Turnaround Time (TAT) is the total time taken from arrival to completion.
Waiting Time (WT) is the time a process spends waiting in the queue, calculated as TAT - Burst Time.
*/
