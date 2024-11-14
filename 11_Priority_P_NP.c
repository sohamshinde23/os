#include <stdio.h>
#include <limits.h>

void find_priority_np(int n, int bt[], int at[], int pr[], int ft[], int tat[], int wt[]) {
    int done[n], min_pr, time = 0, highest;
    for (int i = 0; i < n; i++) done[i] = 0;
    for (int i = 0; i < n; i++) {
        min_pr = INT_MAX;
        highest = -1;
        for (int j = 0; j < n; j++) {
            if (at[j] <= time && !done[j] && pr[j] < min_pr) {
                min_pr = pr[j];
                highest = j;
            }
        }
        if (highest != -1) {
            time += bt[highest];
            ft[highest] = time;
            tat[highest] = ft[highest] - at[highest];
            wt[highest] = tat[highest] - bt[highest];
            done[highest] = 1;
        } else {
            time++;
            i--;
        }
    }
}

void find_priority_p(int n, int bt[], int at[], int pr[], int ft[], int tat[], int wt[]) {
    int bt_rem[n], time = 0, completed = 0, highest_priority, min_priority;
    for (int i = 0; i < n; i++) bt_rem[i] = bt[i];

    while (completed < n) {
        highest_priority = -1;
        min_priority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (at[i] <= time && bt_rem[i] > 0 && pr[i] < min_priority) {
                min_priority = pr[i];
                highest_priority = i;
            }
        }

        if (highest_priority == -1) {
            time++;
            continue;
        }

        bt_rem[highest_priority]--;
        time++;

        if (bt_rem[highest_priority] == 0) {
            completed++;
            ft[highest_priority] = time;
            tat[highest_priority] = ft[highest_priority] - at[highest_priority];
            wt[highest_priority] = tat[highest_priority] - bt[highest_priority];
        }
    }
}

void print_times(int n, int pr[], int at[], int bt[], int ft[], int tat[], int wt[]) {
    printf("Process\tPriority\tArrival Time\tBurst Time\tFinish Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i+1, pr[i], at[i], bt[i], ft[i], tat[i], wt[i]);
    }
}

int main() {
    int n, bt[20], at[20], pr[20], ft[20], tat[20], wt[20], choice;

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
    printf("Enter priorities: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pr[i]);
    }

    printf("Choose Priority Scheduling Type:\n");
    printf("1. Non-Preemptive Priority Scheduling\n");
    printf("2. Preemptive Priority Scheduling\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        find_priority_np(n, bt, at, pr, ft, tat, wt);
    } else if (choice == 2) {
        find_priority_p(n, bt, at, pr, ft, tat, wt);
    } else {
        printf("Invalid choice!\n");
        return 1;
    }

    print_times(n, pr, at, bt, ft, tat, wt);

    return 0;
}

/*
4
3
1
7
4
2
1
0
3
2
1
3
4
2
*/


/*
This code implements **Priority Scheduling** in two forms:
1. **Non-Preemptive Priority Scheduling**: Once a process starts execution, it completes before another process can start, regardless of priority.
2. **Preemptive Priority Scheduling**: If a new process arrives with a higher priority, it can interrupt the currently running process.

Both scheduling methods are coded in separate functions and chosen by the user at runtime.

Let’s break down each part of the code:

---

### 1. `find_priority_np` - Non-Preemptive Priority Scheduling

This function simulates the non-preemptive priority scheduling.

```c
void find_priority_np(int n, int bt[], int at[], int pr[], int ft[], int tat[], int wt[])
```

- **Parameters**:
  - `n`: Number of processes.
  - `bt[]`: Array of burst times for each process.
  - `at[]`: Array of arrival times for each process.
  - `pr[]`: Array of priorities for each process.
  - `ft[]`: Array to store finish times for each process.
  - `tat[]`: Array to store turnaround times for each process.
  - `wt[]`: Array to store waiting times for each process.

#### Variables

- `done[]`: Array to mark completed processes, initialized to 0.
- `time`: Keeps track of the current time.
- `min_pr`: Tracks the lowest priority value found in the iteration.
- `highest`: Index of the highest-priority process that is ready for execution.

#### Scheduling Loop
```c
for (int i = 0; i < n; i++) {
    min_pr = INT_MAX;
    highest = -1;
```

- The loop runs `n` times (once per process) to find and execute the highest-priority, uncompleted process.

1. **Finding the Highest-Priority Process**:
   ```c
   for (int j = 0; j < n; j++) {
       if (at[j] <= time && !done[j] && pr[j] < min_pr) {
           min_pr = pr[j];
           highest = j;
       }
   }
   ```
   - Iterates over all processes.
   - Selects the process with the highest priority (`pr[j] < min_pr`) that has arrived (`at[j] <= time`) and is not yet completed (`!done[j]`).

2. **Process Execution**:
   ```c
   if (highest != -1) {
       time += bt[highest];
       ft[highest] = time;
       tat[highest] = ft[highest] - at[highest];
       wt[highest] = tat[highest] - bt[highest];
       done[highest] = 1;
   }
   ```
   - If a process was found (`highest != -1`):
     - The `time` advances by the process's burst time.
     - Finish time (`ft[highest]`), turnaround time (`tat[highest]`), and waiting time (`wt[highest]`) are calculated for the selected process.
     - Marks the process as completed.

3. **No Process Available**:
   ```c
   else {
       time++;
       i--;
   }
   ```
   - If no process is available at the current time, `time` increments, and the loop index (`i`) is decremented to retry the current iteration.

---

### 2. `find_priority_p` - Preemptive Priority Scheduling

This function simulates preemptive priority scheduling, allowing higher-priority processes to interrupt lower-priority ones.

```c
void find_priority_p(int n, int bt[], int at[], int pr[], int ft[], int tat[], int wt[])
```

- This function has the same parameters as the non-preemptive version, except it also maintains an array for remaining burst times.

#### Variables

- `bt_rem[]`: An array tracking remaining burst time for each process, initialized with `bt[]`.
- `time`: Tracks the current system time.
- `completed`: Counter for completed processes.
- `highest_priority` and `min_priority`: Track the process with the highest priority and the lowest priority value among the uncompleted processes.

#### Scheduling Loop
```c
while (completed < n) {
    highest_priority = -1;
    min_priority = INT_MAX;
```

- The `while` loop continues until all processes have completed.

1. **Finding the Process with Highest Priority**:
   ```c
   for (int i = 0; i < n; i++) {
       if (at[i] <= time && bt_rem[i] > 0 && pr[i] < min_priority) {
           min_priority = pr[i];
           highest_priority = i;
       }
   }
   ```
   - Searches for the process with the highest priority among processes that have arrived and have remaining burst time.

2. **Executing the Highest Priority Process**:
   ```c
   if (highest_priority == -1) {
       time++;
       continue;
   }
   bt_rem[highest_priority]--;
   time++;
   ```
   - If no process is found, the time increments.
   - Otherwise, the highest-priority process is executed for one time unit, and its remaining burst time (`bt_rem[highest_priority]`) is reduced by 1.

3. **Completion of a Process**:
   ```c
   if (bt_rem[highest_priority] == 0) {
       completed++;
       ft[highest_priority] = time;
       tat[highest_priority] = ft[highest_priority] - at[highest_priority];
       wt[highest_priority] = tat[highest_priority] - bt[highest_priority];
   }
   ```
   - When a process's remaining burst time reaches zero, it is marked as completed.
   - The finish time, turnaround time, and waiting time are calculated and stored.

---

### 3. `print_times` - Display Function

```c
void print_times(int n, int pr[], int at[], int bt[], int ft[], int tat[], int wt[])
```

- **Parameters**: Receives all the arrays storing process details.
- **Purpose**: Displays each process's priority, arrival time, burst time, finish time, turnaround time, and waiting time in a formatted table.

---

### 4. `main` Function

```c
int main() {
    int n, bt[20], at[20], pr[20], ft[20], tat[20], wt[20], choice;
```

- Defines arrays for burst time (`bt[]`), arrival time (`at[]`), priority (`pr[]`), finish time (`ft[]`), turnaround time (`tat[]`), and waiting time (`wt[]`).
- `choice`: Stores the user’s choice of scheduling type.

#### User Input
```c
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
printf("Enter priorities: ");
for (int i = 0; i < n; i++) {
    scanf("%d", &pr[i]);
}
```

- Prompts the user to enter the number of processes and their respective burst times, arrival times, and priorities.

#### Scheduling Type Selection
```c
printf("Choose Priority Scheduling Type:\n");
printf("1. Non-Preemptive Priority Scheduling\n");
printf("2. Preemptive Priority Scheduling\n");
printf("Enter your choice: ");
scanf("%d", &choice);
```

- Asks the user to select either non-preemptive or preemptive scheduling.

#### Function Call
```c
if (choice == 1) {
    find_priority_np(n, bt, at, pr, ft, tat, wt);
} else if (choice == 2) {
    find_priority_p(n, bt, at, pr, ft, tat, wt);
} else {
    printf("Invalid choice!\n");
    return 1;
}
print_times(n, pr, at, bt, ft, tat, wt);
```

- Depending on the user’s choice, calls either `find_priority_np` (non-preemptive) or `find_priority_p` (preemptive) function.
- Finally, `print_times` is called to display the results.

---

### Summary

- **Non-Preemptive Priority Scheduling** (`find_priority_np`): Executes each process with the highest priority that is ready, without interruption.
- **Preemptive Priority Scheduling** (`find_priority_p`): Allows interruptions if a new process arrives with a higher priority.
- The output includes each process’s priority, arrival time, burst time, finish time, turnaround time, and waiting time.
*/