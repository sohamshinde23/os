#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the maximum number of valid opcodes
#define MAX_OPCODES 5

// Function to simulate an interrupt (error)
void raise_interrupt(const char *error_message) {
    printf("Error: %s\n", error_message);
    printf("Interrupt raised! Exiting the program...\n");
    exit(1); // Terminate the program on error
}

// Function to check if the opcode is valid
int is_valid_opcode(const char *opcode) {
    // List of valid opcodes
    const char *valid_opcodes[MAX_OPCODES] = {"LOAD", "ADD", "SUB", "STORE", "JMP"};
    
    for (int i = 0; i < MAX_OPCODES; i++) {
        if (strcmp(opcode, valid_opcodes[i]) == 0) {
            return 1; // Valid opcode
        }
    }
    return 0; // Invalid opcode
}

// Function to process the job (list of instructions)
void process_job(const char instructions[][10], int num_instructions) {
    for (int i = 0; i < num_instructions; i++) {
        printf("Processing instruction: %s\n", instructions[i]);
        
        // Check if the opcode is valid
        if (!is_valid_opcode(instructions[i])) {
            raise_interrupt("Invalid opcode encountered!");
        }
    }
    printf("All instructions processed successfully.\n");
}

int main() {
    int num_instructions;
    
    // Ask the user for the number of instructions
    printf("Enter the number of instructions: ");
    scanf("%d", &num_instructions);

    // Array to store instructions
    char instructions[num_instructions][10];
    
    // Take input instructions from the user
    printf("Enter the instructions (one per line):\n");
    for (int i = 0; i < num_instructions; i++) {
        scanf("%s", instructions[i]);
    }
    
    // Process the job and check for opcode errors
    process_job(instructions, num_instructions);
    
    return 0;
}

/*
Enter the number of instructions: 3
Enter the instructions (one per line):
LOAD
ADD
STORE
*/


/*
#include <stdio.h>: This header is for input and output functions (printf, scanf, etc.).
#include <stdlib.h>: Provides functions for memory allocation, process control, and other utilities (exit(), malloc(), etc.).
#include <string.h>: Provides string manipulation functions like strcmp().
#define MAX_OPCODES 5: This is a macro that defines the maximum number of valid opcodes (5 in this case).

Purpose: This function simulates an interrupt, which is a kind of error that forces the program to stop.
Parameters: It takes an error_message string as input, which describes the error encountered.
Logic:
It prints the error message to the console using printf().
It then prints an additional message saying that an interrupt was raised and the program will terminate.
Finally, the program is terminated using exit(1), where 1 is the exit status (indicating failure).

Purpose: This function checks whether a given opcode (instruction) is valid by comparing it against a predefined list of valid opcodes.
Parameters: opcode is the opcode (instruction) to be checked.
Logic:
The function defines an array valid_opcodes[] that contains all the valid opcodes (in this case: "LOAD", "ADD", "SUB", "STORE", "JMP").
The function uses a loop to compare the provided opcode with each valid opcode using strcmp().
If strcmp() finds a match, it returns 1, indicating that the opcode is valid.
If no match is found after checking all valid opcodes, it returns 0, indicating an invalid opcode.

Purpose: This function processes a list of instructions (opcodes) and checks each one for validity.
Parameters:
instructions[][10]: A 2D array containing the instructions. The array is designed to store up to num_instructions opcodes, each with a maximum length of 10 characters.
num_instructions: The number of instructions to process.
Logic:
The function loops over each instruction in the instructions array.
For each instruction, it prints a message saying that the instruction is being processed.
It then checks if the opcode is valid by calling the is_valid_opcode() function.
If an invalid opcode is found, it raises an interrupt using the raise_interrupt() function and stops the program.
If all instructions are valid, it prints a success message.

Purpose: The main() function is the entry point of the program. It interacts with the user, accepts input for the number of instructions and the instructions themselves, and processes them.
Logic:
It first asks the user for the number of instructions they want to input (num_instructions).
It then declares a 2D array instructions[num_instructions][10] to store the instructions. The 10 indicates that each instruction can be up to 9 characters long (plus a null terminator).
The program then asks the user to input the instructions one by one. The scanf("%s", instructions[i]); reads each instruction as a string and stores it in the instructions array.
After all instructions are input, the program calls process_job() to check each instruction for validity.
If all instructions are valid, the program prints "All instructions processed successfully." Otherwise, it will terminate upon encountering an invalid opcode.
Summary of How the Code Works:
The program first asks the user how many instructions they will input and then prompts them to enter each instruction one by one.
For each instruction, the program checks if it matches any of the predefined valid opcodes (LOAD, ADD, SUB, STORE, JMP).
If an invalid opcode is found, the program raises an error and terminates. If all instructions are valid, it prints a success message.
If an invalid opcode is encountered, the program calls the raise_interrupt() function, which prints an error message and terminates the program using exit(1).


*/