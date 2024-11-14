#include <stdio.h>

void fifo(int ref[], int n, int frames) {
    int frame[frames], page_faults = 0, index = 0;
    for (int i = 0; i < frames; i++) frame[i] = -1;
    printf("\nFIFO Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == ref[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            frame[index] = ref[i];
            index = (index + 1) % frames;
            page_faults++;
        }
        printf("Page %d: ", ref[i]);
        for (int j = 0; j < frames; j++) {
            if (frame[j] != -1) printf("%d ", frame[j]);
            else printf("- ");
        }
        printf("\n");
    }
    printf("Total Page Faults (FIFO): %d\n", page_faults);
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

    fifo(ref, n, frames);

    return 0;
}

//input
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

Total 10 
*/


/*
This code is an implementation of the **FIFO (First-In-First-Out) Page Replacement Algorithm** used in operating systems to manage memory. It keeps track of page faults in the process of loading pages into frames.

### Key Concepts of FIFO Page Replacement
- **Pages**: A reference string representing pages being accessed by a process.
- **Frames**: The number of available slots in memory to hold pages.
- **Page Fault**: Occurs when a page is not found in the frame, necessitating it to be loaded into memory.

### Code Explanation

1. **Main Function**
   - The `main` function collects user inputs, such as:
     - `n`: the number of pages in the reference string.
     - `ref[]`: the reference string array that represents the sequence of page accesses.
     - `frames`: the number of frames available in memory.
   - Once the input is collected, it calls the `fifo` function to perform the FIFO page replacement.

2. **FIFO Function (`fifo`)**
   - **Parameters**:
     - `ref[]`: Reference string of pages.
     - `n`: Total number of pages in the reference string.
     - `frames`: Number of frames available in memory.
   - **Variables**:
     - `frame[]`: An array representing the memory frames (initialized to `-1`, indicating an empty frame).
     - `page_faults`: Counter for page faults (initialized to 0).
     - `index`: Tracks which frame to replace (initialized to 0 for FIFO behavior).

3. **FIFO Page Replacement Logic**
   - **Initialize Frames**: All frames are initially set to `-1` to indicate they are empty.
   - **Iterate Over Pages**:
     - For each page in the reference string:
       - **Page Check**:
         - Check if the page is already in one of the frames (`frame[j] == ref[i]`). If it is found, `found` is set to `1`, and no page fault occurs.
       - **Page Fault Handling**:
         - If the page is not found in any frame (`found == 0`), a page fault occurs:
           - The new page (`ref[i]`) is inserted into the `frame[index]` position, replacing the oldest page in FIFO order.
           - The `index` is incremented (modulo `frames`), ensuring it loops back to the start once all frames are filled.
           - The `page_faults` counter is incremented to track page faults.
       - **Display Frame Status**:
         - After each page reference, the program prints the current status of each frame, showing which pages are loaded in each frame slot.
   - **Output Total Page Faults**:
     - After processing the entire reference string, the function prints the total number of page faults.

4. **Example Output**
   - For a reference string like `{0, 1, 2, 3, 0, 1, 4, 0, 1, 2, 3, 4}` and 3 frames, the program outputs which pages are in each frame after each page reference, and finally the total number of page faults.

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
This code demonstrates FIFO page replacement, where each new page that causes a page fault replaces the oldest page in memory. This results in a total count of page faults based on the reference string and available frames.
*/