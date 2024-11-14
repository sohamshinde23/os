#include <stdio.h>
#include <stdlib.h>

void fcfs_disk_scheduling(int requests[], int n, int start) {
    int total_seek_time = 0;
    int current_position = start;

    printf("\nFCFS Disk Scheduling\n");
    printf("%-20s%-20s%-20s\n", "Current Position", "Requested Track", "Seek Time");

    for (int i = 0; i < n; i++) {
        int seek_time = abs(current_position - requests[i]);
        total_seek_time += seek_time;
        printf("%-20d%-20d%-20d\n", current_position, requests[i], seek_time);
        current_position = requests[i];
    }

    printf("\nTotal Seek Time: %d\n", total_seek_time);
}

int main() {
    int n, start_position;

    printf("Enter the starting position of the disk head: ");
    scanf("%d", &start_position);

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the disk requests:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    fcfs_disk_scheduling(requests, n, start_position);
    return 0;
}

// input
/*
100
9
55
58
39
18
90
160
150
38
184
*/


/*
Here’s an explanation of the FCFS (First-Come, First-Served) disk scheduling program:

### **Overview:**
The program simulates the FCFS disk scheduling algorithm, where the disk head services disk requests in the order they arrive. The primary goal of the algorithm is to compute the total seek time while traversing the disk request queue.

### **Code Explanation:**

#### **1. `fcfs_disk_scheduling()` function:**

This function simulates the FCFS disk scheduling algorithm and calculates the total seek time as the disk head moves through the requests.

```c
void fcfs_disk_scheduling(int requests[], int n, int start) {
    int total_seek_time = 0;
    int current_position = start;

    printf("\nFCFS Disk Scheduling\n");
    printf("%-20s%-20s%-20s\n", "Current Position", "Requested Track", "Seek Time");

    for (int i = 0; i < n; i++) {
        int seek_time = abs(current_position - requests[i]);  // Calculate seek time
        total_seek_time += seek_time;  // Add seek time to the total
        printf("%-20d%-20d%-20d\n", current_position, requests[i], seek_time);  // Print details
        current_position = requests[i];  // Update current position to the requested track
    }

    printf("\nTotal Seek Time: %d\n", total_seek_time);  // Print total seek time
}
```

- **Input Parameters:**
  - `requests[]`: An array holding the disk requests (the tracks the disk head has to visit).
  - `n`: The total number of disk requests.
  - `start`: The starting position of the disk head.

- **Process:**
  - The variable `total_seek_time` tracks the sum of all the seek times.
  - The `current_position` variable holds the current position of the disk head, which starts at `start`.
  - For each request:
    - The program calculates the **seek time** (the time to move from the current position to the requested track) using the formula:
      ```
      seek_time = abs(current_position - requests[i])
      ```
    - The seek time is added to `total_seek_time`.
    - The current position is updated to the requested track (`current_position = requests[i]`).
    - The details of the current request (current position, requested track, and seek time) are printed in a tabular format.
  - After iterating through all requests, the program prints the **total seek time**, which is the sum of all the individual seek times.

#### **2. `main()` function:**

The `main()` function is where the user inputs the data and where the `fcfs_disk_scheduling()` function is called.

```c
int main() {
    int n, start_position;

    printf("Enter the starting position of the disk head: ");
    scanf("%d", &start_position);  // Input the starting position of the disk head

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);  // Input the number of disk requests

    int requests[n];
    printf("Enter the disk requests:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);  // Input each disk request
    }

    fcfs_disk_scheduling(requests, n, start_position);  // Call FCFS disk scheduling function
    return 0;
}
```

- **Steps:**
  1. **Input the starting position of the disk head:**
     - The program prompts the user to enter the initial position of the disk head (`start_position`).
  
  2. **Input the number of disk requests:**
     - The program then asks for the number of disk requests (`n`).
  
  3. **Input the disk requests:**
     - The user inputs each disk request. These are the tracks the disk head must visit in the order they arrive.
  
  4. **Call `fcfs_disk_scheduling()`:**
     - The `fcfs_disk_scheduling()` function is called with the inputs: the `requests` array, the number of requests `n`, and the starting position of the disk head.

  5. **Output:**
     - After processing the requests, the program prints the total seek time, and the seek time for each individual request is displayed in a tabular format.

### **Key Concepts:**
1. **Seek Time Calculation:**
   - The seek time is the absolute difference between the current position of the disk head and the requested track. This is calculated using the `abs()` function.
  
2. **FCFS Scheduling:**
   - The disk head services the requests in the order they arrive (first come, first served).
  
3. **Seek Time Summation:**
   - The total seek time is the sum of all individual seek times as the disk head moves from one request to the next.

### **Example:**
For input:
```
Enter the starting position of the disk head: 50
Enter the number of disk requests: 5
Enter the disk requests:
82 170 43 140 24
```

The program would output:

```
FCFS Disk Scheduling
Current Position    Requested Track     Seek Time         
50                  82                  32                
82                  170                 88                
170                 43                  127               
43                  140                 97                
140                 24                  116               

Total Seek Time: 460
```

### **Conclusion:**
This program provides a clear simulation of the FCFS disk scheduling algorithm. It calculates the total seek time for all disk requests and prints the seek times in a tabular format. It helps visualize how the disk head moves through the request queue and provides a basic implementation of one of the simplest disk scheduling algorithms.
*/