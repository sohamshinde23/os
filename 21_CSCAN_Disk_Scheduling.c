#include <stdio.h>
#include <stdlib.h>

void cscan_disk_scheduling(int requests[], int n, int start) {
    int total_seek_time = 0;
    int current_position = start;
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    int index = 0;
    while (index < n && requests[index] < current_position) {
        index++;
    }

    int disk_size = requests[n - 1];  

    printf("\nC-SCAN Disk Scheduling\n");
    printf("%-20s%-20s%-20s\n", "Current Position", "Requested Track", "Seek Time");

    for (int i = index; i < n; i++) {
        int seek_time = abs(current_position - requests[i]);
        total_seek_time += seek_time;
        printf("%-20d%-20d%-20d\n", current_position, requests[i], seek_time);
        current_position = requests[i];
    }

    int seek_time = abs(current_position - disk_size);
    total_seek_time += seek_time;
    printf("%-20d%-20d%-20d\n", current_position, disk_size, seek_time);
    current_position = disk_size;

    seek_time = abs(current_position - 0);
    total_seek_time += seek_time;
    printf("%-20d%-20d%-20d\n", current_position, 0, seek_time);
    current_position = 0;

    for (int i = 0; i < index; i++) {
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

    cscan_disk_scheduling(requests, n, start_position);

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
*/


/*
This C program implements the **C-SCAN (Circular SCAN) disk scheduling** algorithm, which is a variation of the SCAN algorithm. In **C-SCAN**, the disk arm moves in one direction (either left or right), and when it reaches the end of the disk, it jumps back to the other end and continues servicing the requests in the same direction.

Let's break down and explain the code step by step:

### **Function: `cscan_disk_scheduling`**
This function performs the **C-SCAN** disk scheduling based on the input disk requests and starting position of the disk head.

#### **Input Parameters:**
- `requests[]`: An array containing the disk track requests that need to be serviced.
- `n`: The number of disk requests.
- `start`: The starting position of the disk head.

#### **Step-by-Step Breakdown:**

1. **Initialize Variables:**
   ```c
   int total_seek_time = 0;
   int current_position = start;
   ```
   - `total_seek_time`: Keeps track of the total seek time (the total amount of time the disk head moves).
   - `current_position`: Keeps track of the current position of the disk head, initially set to the starting position.

2. **Sorting the Requests:**
   ```c
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
   - This is a simple **Bubble Sort** to sort the `requests[]` array in ascending order. The disk head will move in the sorted order.

3. **Finding the Index of the First Request Greater Than or Equal to `current_position`:**
   ```c
   int index = 0;
   while (index < n && requests[index] < current_position) {
       index++;
   }
   ```
   - The program looks for the first request in the sorted list that is greater than or equal to the current position of the disk head. This determines the starting point for the rightward traversal.

4. **Finding the Disk Size:**
   ```c
   int disk_size = requests[n - 1];
   ```
   - The `disk_size` is set to the last request in the sorted `requests[]` array, assuming that the disk size is at least as large as the highest request.

5. **Move the Disk Head to the Right:**
   ```c
   for (int i = index; i < n; i++) {
       int seek_time = abs(current_position - requests[i]);
       total_seek_time += seek_time;
       printf("%-20d%-20d%-20d\n", current_position, requests[i], seek_time);
       current_position = requests[i];
   }
   ```
   - The disk head services all the requests from the `index` position (first request greater than or equal to the current position) to the rightmost position (the last request).
   - For each request, the program calculates the **seek time** (absolute difference between the current position and the request).
   - The `total_seek_time` is updated with the seek time for each request.

6. **Move to the End of the Disk (`disk_size`) and Jump to the Beginning (0):**
   ```c
   int seek_time = abs(current_position - disk_size);
   total_seek_time += seek_time;
   printf("%-20d%-20d%-20d\n", current_position, disk_size, seek_time);
   current_position = disk_size;

   seek_time = abs(current_position - 0);
   total_seek_time += seek_time;
   printf("%-20d%-20d%-20d\n", current_position, 0, seek_time);
   current_position = 0;
   ```
   - Once all requests in the rightward direction are serviced, the head moves to the **end of the disk** (disk size) and jumps to the **beginning** (track 0).
   - Seek times are calculated for these jumps, and the `total_seek_time` is updated.

7. **Service Remaining Requests from the Beginning:**
   ```c
   for (int i = 0; i < index; i++) {
       int seek_time = abs(current_position - requests[i]);
       total_seek_time += seek_time;
       printf("%-20d%-20d%-20d\n", current_position, requests[i], seek_time);
       current_position = requests[i];
   }
   ```
   - After jumping to track 0, the disk head moves to the remaining unserviced requests that are located before the initial `current_position`.
   - These requests are serviced in the same order, and seek times are calculated and added to `total_seek_time`.

8. **Print Total Seek Time:**
   ```c
   printf("\nTotal Seek Time: %d\n", total_seek_time);
   ```
   - Finally, the total seek time is printed, which is the sum of all the seek times for each move the disk head made during the entire process.

---

### **Main Function:**

- The main function handles user input and invokes the `cscan_disk_scheduling` function.

1. **Input Parameters:**
   - `start_position`: The starting position of the disk head (entered by the user).
   - `n`: The number of disk requests (entered by the user).
   - `requests[]`: An array of disk requests (entered by the user).

2. **Call `cscan_disk_scheduling`:**
   - The main function passes the input data to the `cscan_disk_scheduling` function to process the disk scheduling.

---

### **Summary of C-SCAN Disk Scheduling:**

1. **Sort** the requests in ascending order.
2. **Move the disk head to the rightmost request** (greater than or equal to the current position).
3. **Move the disk head to the end of the disk** and jump to track 0.
4. **Service remaining requests** that are smaller than the initial current position.
5. **Print the seek time** for each move and calculate the **total seek time**.

### **Output:**
- The program prints the current position, the requested track, and the seek time for each move the disk head makes, followed by the total seek time after processing all requests.


*/