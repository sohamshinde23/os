//lru
#include <stdio.h>

void lru(int ref[], int n, int frames) {
    int frame[frames], page_faults = 0, time[frames], least, found;
    for (int i = 0; i < frames; i++) frame[i] = -1;
    for (int i = 0; i < frames; i++) time[i] = -1;
    printf("\nLRU Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        found = 0;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == ref[i]) {
                found = 1;
                time[j] = i;
                break;
            }
        }
        if (!found) {
            least = 0;
            for (int j = 1; j < frames; j++) {
                if (time[j] < time[least]) least = j;
            }
            frame[least] = ref[i];
            time[least] = i;
            page_faults++;
        }
        printf("Page %d: ", ref[i]);
        for (int j = 0; j < frames; j++) {
            if (frame[j] != -1) printf("%d ", frame[j]);
            else printf("- ");
        }
        printf("\n");
    }
    printf("Total Page Faults (LRU): %d\n", page_faults);
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

    lru(ref, n, frames);

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
This code is an implementation of the **LRU (Least Recently Used) Page Replacement Algorithm**, which is used in operating systems to manage memory. This algorithm loads pages into frames while keeping track of page faults and replaces the least recently used page in the frame when necessary.

### Key Concepts of LRU Page Replacement
- **Pages**: A reference string representing pages being accessed by a process.
- **Frames**: The number of slots available in memory to hold pages.
- **Page Fault**: Occurs when a page is not found in any of the frames, requiring it to be loaded into memory.
- **Least Recently Used**: The page that was accessed the farthest back in time is replaced when a new page is loaded into a full set of frames.

### Code Explanation

1. **Main Function**
   - Collects user inputs:
     - `n`: the number of pages in the reference string.
     - `ref[]`: the reference string array representing the sequence of page accesses.
     - `frames`: the number of frames available in memory.
   - Once the input is collected, it calls the `lru` function to perform the LRU page replacement.

2. **LRU Function (`lru`)**
   - **Parameters**:
     - `ref[]`: The reference string of pages.
     - `n`: The total number of pages in the reference string.
     - `frames`: The number of frames available in memory.
   - **Variables**:
     - `frame[]`: An array representing the memory frames, initialized to `-1` (indicating empty frames).
     - `page_faults`: Counts the number of page faults (initialized to 0).
     - `time[]`: Keeps track of the time each page was last used in the frames.
     - `least`: Stores the index of the least recently used frame.

3. **LRU Page Replacement Logic**
   - **Initialize Frames**: All frames are initially set to `-1` to indicate they are empty, and `time[]` is initialized to `-1` to signify that no pages have been loaded.
   - **Iterate Over Pages**:
     - For each page in the reference string:
       - **Page Check**:
         - The algorithm checks if the page is already present in any frame (`frame[j] == ref[i]`). If found, `found` is set to 1, and the current index `i` is recorded in `time[j]` (indicating the last access time for that page).
       - **Page Fault Handling**:
         - If the page is not found in any frame (`found == 0`), a page fault occurs:
           - The least recently used frame is found by checking which frame has the smallest `time` value.
           - The new page (`ref[i]`) is inserted into `frame[least]`, replacing the least recently used page.
           - The current time `i` is updated in `time[least]` to record this page's last access time.
           - The `page_faults` counter is incremented.
       - **Display Frame Status**:
         - After each page reference, the program prints the current status of each frame, showing which pages are loaded in each frame slot.
   - **Output Total Page Faults**:
     - After processing the entire reference string, the function prints the total number of page faults.

4. **Example Output**
   - For a reference string like `{0, 1, 2, 3, 0, 1, 4, 0, 1, 2, 3, 4}` and 3 frames, the program outputs the page loaded in each frame after each reference and finally prints the total number of page faults.

### Code Execution Flow Example
Suppose the reference string is `{1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5}` and we have 3 frames.

| Page | Frame Contents        | Page Fault |
|------|------------------------|------------|
| 1    | 1 - -                 | Yes        |
| 2    | 1 2 -                 | Yes        |
| 3    | 1 2 3                 | Yes        |
| 4    | 4 2 3                 | Yes        |
| 1    | 4 1 3                 | Yes        |
| 2    | 4 1 2                 | Yes        |
| 5    | 5 1 2                 | Yes        |
| 1    | 5 1 2                 | No         |
| 2    | 5 1 2                 | No         |
| 3    | 3 1 2                 | Yes        |
| 4    | 3 4 2                 | Yes        |
| 5    | 3 4 5                 | Yes        |

- **Total Page Faults**: 9

### Summary
This code implements the LRU page replacement algorithm, which loads pages into frames and replaces the page that has been unused the longest whenever a page fault occurs and all frames are full. It calculates the total number of page faults based on the reference string and available frames, providing insight into the efficiency of the LRU algorithm for memory management.
*/