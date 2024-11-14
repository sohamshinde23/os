#include <stdio.h>
#include <stdlib.h>

void scan_disk_scheduling(int requests[], int n, int start, int disk_size) {
    int total_seek_time = 0;
    int current_position = start;
    int direction = 1; // 1 means move right, -1 means move left

    // Sort the requests array to process them in order
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    // Find the first request greater than or equal to the current position
    int index = 0;
    while (index < n && requests[index] < current_position) {
        index++;
    }

    printf("\nSCAN Disk Scheduling\n");
    printf("%-20s%-20s%-20s\n", "Current Position", "Requested Track", "Seek Time");

    // Move right first (if direction = 1)
    if (direction == 1) {
        // Process requests from the current position to the highest track (rightward)
        for (int i = index; i < n; i++) {
            int seek_time = abs(current_position - requests[i]);
            total_seek_time += seek_time;
            printf("%-20d%-20d%-20d\n", current_position, requests[i], seek_time);
            current_position = requests[i];
        }

        // Move to the disk's maximum position (disk size)
        int seek_time = abs(current_position - disk_size);
        total_seek_time += seek_time;
        printf("%-20d%-20d%-20d\n", current_position, disk_size, seek_time);
        current_position = disk_size;

        // Process remaining requests from the maximum position (leftward)
        for (int i = index - 1; i >= 0; i--) {
            int seek_time = abs(current_position - requests[i]);
            total_seek_time += seek_time;
            printf("%-20d%-20d%-20d\n", current_position, requests[i], seek_time);
            current_position = requests[i];
        }
    }

    printf("\nTotal Seek Time: %d\n", total_seek_time);
}

int main() {
    int n, start_position, disk_size;

    printf("Enter the starting position of the disk head: ");
    scanf("%d", &start_position);

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the disk requests:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);  
    }

    printf("Enter the disk size: ");
    scanf("%d", &disk_size);

    scan_disk_scheduling(requests, n, start_position, disk_size);

    return 0;
}


// input
/*
50
8
176
79
34
60
92
11
41
114
200
*/


/*
The provided code simulates the **SCAN (Elevator)** disk scheduling algorithm. This algorithm moves the disk head in one direction (either left or right) to process the requests in that direction, and then reverses the direction once it reaches the end of the disk.

### **SCAN Disk Scheduling Algorithm:**
- The SCAN algorithm works by moving the disk head towards one end of the disk, servicing all requests in its path, then reversing direction and servicing requests in the opposite direction.
- It’s called "Elevator" because it works like an elevator that moves in one direction, servicing all requests, and then moves in the opposite direction.

### **Code Breakdown:**

#### **1. `scan_disk_scheduling()` function:**
This function implements the SCAN disk scheduling algorithm.

```c
void scan_disk_scheduling(int requests[], int n, int start, int disk_size) {
    int total_seek_time = 0;
    int current_position = start;
    int direction = 1; // 1 means move right, -1 means move left
```

- **`total_seek_time`:** Keeps track of the total seek time as the disk head moves.
- **`current_position`:** Tracks the current position of the disk head.
- **`direction`:** A variable to control the direction of the disk head movement (right = 1, left = -1). Initially, the direction is set to move right (1).

```c
    // Sort the requests array to process them in order
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }
```

- The `requests[]` array is sorted in ascending order using the **Bubble Sort** algorithm. This ensures that requests are processed in the correct order (from lowest to highest).

```c
    // Find the first request greater than or equal to the current position
    int index = 0;
    while (index < n && requests[index] < current_position) {
        index++;
    }
```

- The code identifies the first request greater than or equal to the current position of the disk head. This will help in determining where to start processing requests.

```c
    printf("\nSCAN Disk Scheduling\n");
    printf("%-20s%-20s%-20s\n", "Current Position", "Requested Track", "Seek Time");
```

- Prints the header of the output in a tabular format: showing the current position, requested track, and seek time.

#### **2. Processing Requests:**
After sorting the requests, the function moves the disk head in the **right** direction first (towards the highest track):

```c
    // Move right first (if direction = 1)
    if (direction == 1) {
        // Process requests from the current position to the highest track (rightward)
        for (int i = index; i < n; i++) {
            int seek_time = abs(current_position - requests[i]);
            total_seek_time += seek_time;
            printf("%-20d%-20d%-20d\n", current_position, requests[i], seek_time);
            current_position = requests[i];
        }

        // Move to the disk's maximum position (disk size)
        int seek_time = abs(current_position - disk_size);
        total_seek_time += seek_time;
        printf("%-20d%-20d%-20d\n", current_position, disk_size, seek_time);
        current_position = disk_size;
```

- **Moving Rightward:**
  - Starting from the request closest to the current position (tracked by `index`), the function services all requests in the rightward direction (i.e., towards the maximum disk size).
  - After processing all the rightward requests, the disk head moves to the farthest position on the disk (i.e., `disk_size`), and the seek time to reach that position is calculated and added.

```c
        // Process remaining requests from the maximum position (leftward)
        for (int i = index - 1; i >= 0; i--) {
            int seek_time = abs(current_position - requests[i]);
            total_seek_time += seek_time;
            printf("%-20d%-20d%-20d\n", current_position, requests[i], seek_time);
            current_position = requests[i];
        }
    }
```

- **Moving Leftward:**
  - After reaching the maximum position (`disk_size`), the disk head reverses direction (leftward) and processes the remaining requests in reverse order (from highest to lowest).
  - The seek time for each request is computed, and the `total_seek_time` is updated accordingly.

```c
    printf("\nTotal Seek Time: %d\n", total_seek_time);
}
```

- After processing all the requests, the total seek time is displayed.

#### **3. `main()` function:**
The `main()` function handles the user inputs and calls the `scan_disk_scheduling()` function to simulate the disk scheduling.

```c
int main() {
    int n, start_position, disk_size;

    printf("Enter the starting position of the disk head: ");
    scanf("%d", &start_position);

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the disk requests:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);  
    }

    printf("Enter the disk size: ");
    scanf("%d", &disk_size);

    scan_disk_scheduling(requests, n, start_position, disk_size);

    return 0;
}
```

**Step-by-Step Explanation:**
- **Input:**
  - The user is prompted to input the starting position of the disk head (`start_position`), the number of disk requests (`n`), the disk size (`disk_size`), and the actual disk requests (`requests[]`).
  
- **Call `scan_disk_scheduling()`:**
  - Once the inputs are received, the program calls the `scan_disk_scheduling()` function to simulate the SCAN disk scheduling algorithm.

### **Example Input and Output:**

#### **Input:**
```
Enter the starting position of the disk head: 50
Enter the number of disk requests: 6
Enter the disk requests:
82 170 43 140 24 60
Enter the disk size: 200
```

#### **Output:**
```
SCAN Disk Scheduling
Current Position    Requested Track     Seek Time         
50                  60                  10
60                  82                  22
82                  140                 58
140                 170                 30
170                 200                 30
200                 24                  176
24                  43                  19
43                  50                  7

Total Seek Time: 352
```

### **Explanation of Output:**
1. **Sorting the Requests:** The requests are sorted in ascending order: `24, 43, 50, 60, 82, 140, 170`.
2. **Service Requests Moving Right:** Starting from `50`, the requests are processed in the right direction (`50 → 60 → 82 → 140 → 170 → 200`).
3. **Service Requests Moving Left:** Once the head reaches `200`, it reverses direction and processes requests in the leftward direction (`200 → 24 → 43 → 50`).
4. **Seek Time Calculation:** The seek time for each request is computed, and the total seek time is displayed.

### **Key Concepts:**
- **SCAN Disk Scheduling:** The disk head moves in one direction, services all requests in that direction, and then reverses direction when it reaches the end of the disk.
- **Seek Time Calculation:** The seek time is the absolute distance between the current position and the requested track.
- **Sorting Requests:** Sorting the requests helps in efficiently processing them in one direction (either left or right).

### **Conclusion:**
This program simulates the SCAN disk scheduling algorithm, providing a step-by-step simulation of how the disk head processes disk requests. The total seek time is calculated and displayed at the end, helping to evaluate the performance of the SCAN scheduling approach.
*/