#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void sstf_disk_scheduling(int requests[], int n, int start) {
    int total_seek_time = 0;
    int current_position = start;
    bool serviced[n];  // Array to mark requests that have been serviced

    for (int i = 0; i < n; i++) {
        serviced[i] = false;  // Initialize all requests as unserviced
    }

    printf("\nSSTF Disk Scheduling\n");
    printf("%-20s%-20s%-20s\n", "Current Position", "Requested Track", "Seek Time");

    for (int i = 0; i < n; i++) {
        int min_seek_time = __INT_MAX__;
        int closest_request = -1;

        // Find the closest unserviced request
        for (int j = 0; j < n; j++) {
            if (!serviced[j]) {
                int seek_time = abs(current_position - requests[j]);
                if (seek_time < min_seek_time) {
                    min_seek_time = seek_time;
                    closest_request = j;
                }
            }
        }

        // Service the closest request
        if (closest_request != -1) {
            serviced[closest_request] = true;
            total_seek_time += min_seek_time;
            printf("%-20d%-20d%-20d\n", current_position, requests[closest_request], min_seek_time);
            current_position = requests[closest_request];
        }
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

    sstf_disk_scheduling(requests, n, start_position);

    return 0;
}


// input
/*
50
5
82
170
43
140
24
*/


/*
The given code simulates the **SSTF (Shortest Seek Time First)** disk scheduling algorithm. This algorithm services the disk requests by selecting the request that is closest to the current position of the disk head, aiming to minimize the seek time (the distance the disk head has to move).

Here’s a detailed explanation of the code:

### **Overview:**
1. **Goal of SSTF:** The SSTF disk scheduling algorithm services the requests in such a way that the disk head moves the shortest distance for each request. At each step, it chooses the unserviced request that has the smallest seek time from the current position of the disk head.
  
2. **Program Functionality:**
   - The user inputs the starting position of the disk head and the list of disk requests (the track numbers).
   - The program calculates the total seek time and services each request one by one, always picking the closest unserviced request.

### **Code Breakdown:**

#### **1. `sstf_disk_scheduling()` function:**

This function implements the SSTF disk scheduling algorithm.

```c
void sstf_disk_scheduling(int requests[], int n, int start) {
    int total_seek_time = 0;
    int current_position = start;
    bool serviced[n];  // Array to mark requests that have been serviced

    for (int i = 0; i < n; i++) {
        serviced[i] = false;  // Initialize all requests as unserviced
    }

    printf("\nSSTF Disk Scheduling\n");
    printf("%-20s%-20s%-20s\n", "Current Position", "Requested Track", "Seek Time");

    for (int i = 0; i < n; i++) {
        int min_seek_time = __INT_MAX__;  // Initialize the minimum seek time to maximum integer value
        int closest_request = -1;

        // Find the closest unserviced request
        for (int j = 0; j < n; j++) {
            if (!serviced[j]) {  // If the request is not yet serviced
                int seek_time = abs(current_position - requests[j]);  // Calculate the seek time to this request
                if (seek_time < min_seek_time) {  // If this request is closer than the previous closest request
                    min_seek_time = seek_time;
                    closest_request = j;  // Mark this request as the closest one
                }
            }
        }

        // Service the closest request
        if (closest_request != -1) {
            serviced[closest_request] = true;  // Mark the request as serviced
            total_seek_time += min_seek_time;  // Add the seek time to the total seek time
            printf("%-20d%-20d%-20d\n", current_position, requests[closest_request], min_seek_time);  // Print the details
            current_position = requests[closest_request];  // Update the current position of the disk head
        }
    }

    printf("\nTotal Seek Time: %d\n", total_seek_time);  // Print the total seek time
}
```

**Step-by-Step Explanation:**
- **Input Parameters:**
  - `requests[]`: An array containing the disk requests (track numbers).
  - `n`: The number of requests.
  - `start`: The starting position of the disk head.

- **Initialize `serviced[]` Array:**
  - This boolean array tracks whether a request has been serviced. Initially, all values are set to `false`.

- **Loop Through Requests:**
  - The outer loop runs `n` times, once for each request, and at each iteration:
    - **Finding the Closest Request:**
      - For each request, the program checks all unserviced requests to find the one with the minimum seek time (the closest to the current disk head position).
      - This is done by calculating the absolute difference between the current disk head position and each unserviced request using `abs(current_position - requests[j])`.
      - If a request is closer than the previously found one, it becomes the new "closest" request.
      
    - **Service the Closest Request:**
      - Once the closest request is identified, it's serviced (i.e., marked as serviced by setting `serviced[closest_request] = true`).
      - The total seek time is updated by adding the seek time for the serviced request.
      - The current position of the disk head is updated to the position of the serviced request.

    - **Print Request Details:**
      - After servicing each request, the program prints the current position of the disk head, the track that was requested, and the seek time for that request in a tabular format.

- **Total Seek Time:**
  - After servicing all requests, the program prints the total seek time, which is the sum of all individual seek times.

#### **2. `main()` function:**

This function handles user input and invokes the `sstf_disk_scheduling()` function to process the disk requests.

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

    sstf_disk_scheduling(requests, n, start_position);  // Call SSTF disk scheduling function
    return 0;
}
```

**Step-by-Step Explanation:**
- **Input the starting position of the disk head:** 
  - The user is prompted to enter the initial position of the disk head (`start_position`).
  
- **Input the number of disk requests:**
  - The user is then asked how many disk requests there are (`n`).
  
- **Input the disk requests:**
  - The program prompts the user to enter the disk requests. These are the track numbers that the disk head needs to visit.
  
- **Call `sstf_disk_scheduling()` function:**
  - The `sstf_disk_scheduling()` function is called with the `requests[]` array, the number of requests (`n`), and the starting position of the disk head.

- **Output:**
  - After processing the requests, the program will output the seek time for each request and the total seek time.

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
SSTF Disk Scheduling
Current Position    Requested Track     Seek Time         
50                  43                  7                
43                  24                  19               
24                  82                  58               
82                  140                 58               
140                 170                 30               

Total Seek Time: 172
```

### **Key Concepts:**
1. **Seek Time Calculation:**
   - The seek time is the absolute difference between the current position of the disk head and the requested track.
  
2. **SSTF Scheduling:**
   - The SSTF algorithm always selects the request that is closest to the current disk head position, minimizing the seek time at each step.

3. **Efficient Request Processing:**
   - The algorithm prioritizes requests that minimize disk head movement, but it can lead to starvation if some requests are always farther away from the disk head.

### **Conclusion:**
This program provides a simulation of the SSTF disk scheduling algorithm, efficiently calculating the total seek time and printing the details of each request serviced. It demonstrates how the disk head services requests in the shortest seek time order.
*/