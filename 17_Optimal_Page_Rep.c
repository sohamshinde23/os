//optimal
#include <stdio.h>

int find_optimal(int ref[], int frame[], int n, int current, int frames) {
    int pos = -1, farthest = current;
    for (int i = 0; i < frames; i++) {
        int j;
        for (j = current; j < n; j++) {
            if (frame[i] == ref[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        if (j == n) return i;
    }
    if (pos == -1) return 0;
    return pos;
}

void optimal(int ref[], int n, int frames) {
    int frame[frames], page_faults = 0, found;
    for (int i = 0; i < frames; i++) frame[i] = -1;
    printf("\nOptimal Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        found = 0;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == ref[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            if (i < frames) frame[i] = ref[i];
            else {
                int pos = find_optimal(ref, frame, n, i + 1, frames);
                frame[pos] = ref[i];
            }
            page_faults++;
        }
        printf("Page %d: ", ref[i]);
        for (int j = 0; j < frames; j++) {
            if (frame[j] != -1) printf("%d ", frame[j]);
            else printf("- ");
        }
        printf("\n");
    }
    printf("Total Page Faults (Optimal): %d\n", page_faults);
}

int main() {
    int n, frames;
    printf("Enter number of pages in the reference string: ");
    scanf("%d", &n);
    int ref[n];
    printf("Enter the reference string: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &ref[i]);
    }
    printf("Enter number of frames: ");
    scanf("%d", &frames);

    optimal(ref, n, frames);

    return 0;
}


/*
12
1
2
3
4
1
2
5
1
2
3
4
5
4
*/


/*
This code implements the **Optimal Page Replacement Algorithm**, which is a page replacement policy used to manage memory in operating systems. The key idea behind the Optimal algorithm is to replace the page that will not be used for the longest period in the future, thereby minimizing page faults.

### Key Concepts of the Optimal Page Replacement Algorithm:
- **Pages**: A sequence of page references made by a process.
- **Frames**: The available slots in memory to hold pages.
- **Page Fault**: Occurs when a page is not present in memory and needs to be loaded.
- **Optimal Replacement**: At each step, the page that will not be needed for the longest time in the future is replaced.

### Code Explanation

#### 1. **Main Function**:
   - **User Input**: 
     - `n`: The number of pages in the reference string (how many page accesses will be simulated).
     - `ref[]`: The reference string array representing the sequence of page accesses.
     - `frames`: The number of frames available in memory.
   - After collecting the input, the `optimal` function is called to simulate the Optimal Page Replacement.

#### 2. **Optimal Function** (`optimal`):
   - **Parameters**:
     - `ref[]`: The reference string of pages.
     - `n`: The total number of pages in the reference string.
     - `frames`: The number of frames in memory to hold pages.
   - **Variables**:
     - `frame[]`: An array representing the frames in memory, initialized to `-1` to indicate empty slots.
     - `page_faults`: Counter for the total number of page faults (initialized to 0).
     - `found`: A flag used to check whether a page is already present in the frames or not.

#### 3. **Optimal Page Replacement Logic**:
   - **Initialize Frames**: Initially, all frames are set to `-1` (empty).
   - **Iterate Through Reference String**:
     - For each page in the reference string:
       - **Page Check**: The algorithm checks if the page is already present in any of the frames (`frame[j] == ref[i]`). If found, it means no page fault occurs, and the page is already in memory.
       - **Page Fault Handling**:
         - If the page is not found in any frame (`found == 0`), a page fault occurs:
           - If there is an empty frame (i.e., not all frames are filled yet), the page is inserted into the first available frame.
           - If all frames are full, the **Optimal Replacement Decision** is made by calling the `find_optimal` function.
     - **Optimal Page Selection**:
       - **`find_optimal()`** is a helper function that determines which page should be replaced:
         - It looks at the pages currently in memory (`frame[]`) and checks when each page will be accessed again in the future. The page that is needed farthest in the future is replaced.
         - If a page is not found in the future references (i.e., it won't be used again), that page is chosen for replacement.
   - **Display Frame Status**: After each reference, the contents of the frames are printed, showing the pages currently in memory. If a frame is empty, it prints a `-` symbol to represent the empty slot.
   - **Output Total Page Faults**: After processing all the pages in the reference string, the program prints the total number of page faults.

#### 4. **`find_optimal()` Function**:
   - **Parameters**:
     - `ref[]`: The reference string of pages.
     - `frame[]`: The current state of the frames.
     - `n`: The total number of pages.
     - `current`: The current index of the page being processed.
     - `frames`: The number of available frames.
   - **Purpose**: This function determines which page to replace based on the optimal algorithm (the page that is used farthest in the future).
   - **Logic**:
     - For each page in memory (`frame[i]`), the function looks ahead in the reference string and tries to find the page that will be accessed last (farthest from the current page).
     - If a page will not be used in the future, it's selected for replacement.
     - If all pages in the frames are needed in the future, it selects the page with the farthest next usage.

#### 5. **Example Execution**:
   For example, with the reference string `{7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3}` and 3 frames:

   | Step | Reference | Frame Status        | Page Fault? |
   |------|-----------|---------------------|-------------|
   | 1    | 7         | 7 - -                | Yes         |
   | 2    | 0         | 7 0 -                | Yes         |
   | 3    | 1         | 7 0 1                | Yes         |
   | 4    | 2         | 2 0 1                | Yes         |
   | 5    | 0         | 2 0 1                | No          |
   | 6    | 3         | 2 3 1                | Yes         |
   | 7    | 0         | 0 3 1                | Yes         |
   | 8    | 4         | 0 3 4                | Yes         |
   | 9    | 2         | 0 2 4                | Yes         |
   | 10   | 3         | 0 2 3                | Yes         |
   | 11   | 0         | 0 2 3                | No          |
   | 12   | 3         | 0 2 3                | No          |

   - **Total Page Faults**: 9

#### 6. **Summary**:
The Optimal Page Replacement algorithm minimizes the number of page faults by replacing the page that will not be used for the longest time in the future. This code simulates the page replacement process for a given reference string and frame size, showing the state of memory after each page access and calculating the total number of page faults. This approach provides a theoretical benchmark for evaluating other page replacement algorithms like FIFO or LRU.
*/