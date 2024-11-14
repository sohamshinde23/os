#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#define FIFO_FILE "my_fifo"

void process_related() {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }



    if (pid == 0) {
        printf("Child process (PID: %d) is running\n", getpid());
        exit(EXIT_SUCCESS);
    } else {
        wait(NULL); 
        printf("Parent process (PID: %d) has waited for child pro-cess\n", getpid());
    }
}

void file_related() {
    int fd = open("example.txt", O_CREAT | O_RDWR, 0644);
    if (fd < 0) {
        perror("open");
        return;
    }
    write(fd, "Hello, world!\n", 14);

    lseek(fd, 0, SEEK_SET);
    char buffer[15];
    read(fd, buffer, 14);
    buffer[14] = '\0';
    printf("Read from file: %s", buffer);

    close(fd);

    // Create a hard link and then delete the original file
    link("example.txt", "example_link.txt");
    unlink("example.txt");

    struct stat st;
    if (stat("example_link.txt", &st) == 0) {
        printf("Link file size: %ld bytes\n", st.st_size);
    }
    unlink("example_link.txt");
}

void communication() {
    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe");
        return;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return;
    }

    if (pid == 0) {
        // Child process
        close(fd[1]);        
        char buffer[100];
        read(fd[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);
        close(fd[0]);
        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        close(fd[0]);        
        write(fd[1], "Hello from parent!", 19);
        close(fd[1]);
        wait(NULL);
    }
}

void info_related() {
    printf("Process ID (PID): %d\n", getpid());
    printf("Parent Process ID (PPID): %d\n", getppid());
    printf("User ID (UID): %d\n", getuid());
    printf("Group ID (GID): %d\n", getgid());
}

int main() {
    int choice;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Process Related\n");
        printf("2. File Related\n");
        printf("3. Communication\n");
        printf("4. Information Related\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                process_related();
                break;
            case 2:
                file_related();
                break;
            case 3:
                communication();
                break;
            case 4:
                info_related();
                break;
            case 5:
                exit(EXIT_SUCCESS);
            default:
                printf("Invalid choice, try again.\n");
        }
    }

    return 0;
}


/*
Menu System (Main Function)
The program presents the user with a menu that has the following options:

Process Related Operations
File Related Operations
Inter-Process Communication (IPC) using pipes
Display Process Information
Exit
The main() function runs in an infinite loop, prompting the user for input and executing the corresponding functionality based on the user's choice.


1. Process-Related Operations (process_related)
The function process_related() demonstrates process creation using fork(). The fork() system call creates a new child process. Both the parent and the child process will execute the code that follows the fork().

Code flow:
Forking a process: The child process is created using fork(). The return value of fork() is 0 for the child and the PID of the child for the parent.
Child process: The child prints its PID and exits immediately using exit().
Parent process: The parent waits for the child process to complete using wait(), then prints that it has waited for the child.

getpid(): Returns the PID of the current process.
wait(NULL): Waits for any child process to finish.

2. File-Related Operations (file_related)
This function demonstrates file handling in Linux:

Opening a file using open().
Writing to a file using write().
Reading from a file using read().
Creating a hard link using link().
Deleting a file using unlink().
Code flow:
Open a file called example.txt with O_CREAT and O_RDWR flags.
Write a string to the file.
Read back from the file and print the content.
Create a hard link to the file (example_link.txt) and then delete the original file.
Use stat() to check the size of the linked file.

open(): Opens a file for reading and writing, creating it if necessary.
lseek(): Moves the file pointer to the beginning of the file.
write() and read(): Write to and read from the file respectively.
link(): Creates a hard link.
unlink(): Deletes a file.
stat(): Retrieves file information (e.g., file size).

3. Inter-Process Communication (IPC) Using Pipes (communication)
This function demonstrates communication between processes using a pipe. A pipe allows data to be passed between the parent and child processes.

Code flow:
The pipe() system call creates a unidirectional communication channel between the parent and the child process.
After forking:
The child process closes the write-end of the pipe, reads from the read-end, and prints the received message.
The parent process closes the read-end of the pipe, writes a message to the pipe, and then waits for the child process to finish.

pipe(fd): Creates a pipe, fd[0] is the read-end, and fd[1] is the write-end.
read() and write(): Transfer data between the processes.
close(): Closes the pipe ends to ensure the processes only read from the read-end and write to the write-end.

4. Process Information (info_related)
This function simply prints out some useful information about the current process:

Process ID (PID): The unique identifier for the current process.
Parent Process ID (PPID): The PID of the parent process.
User ID (UID): The UID of the user who started the process.
Group ID (GID): The GID of the user who started the process.

getpid(): Returns the PID of the current process.
getppid(): Returns the PID of the parent process.
getuid() and getgid(): Return the UID and GID of the current process.

Exit and Loop Control
The program will continue to display the menu and execute the chosen operations until the user selects option 5 (Exit), which terminates the program using exit(EXIT_SUCCESS).
Conclusion
This program covers several important system programming concepts in Unix/Linux:

Process creation and management using fork() and wait().
File operations like creating, reading, writing, and linking files.
Inter-process communication via pipes (pipe()).
Retrieving system information using functions like getpid(), getppid(), and getuid().
*/