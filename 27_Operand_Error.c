#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define maximum number of valid opcodes and operand range
#define MAX_OPCODES 5
#define MAX_OPERAND 100 // Define the range of valid operands (e.g., 0 to 100)

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

// Function to check if the operand is valid
int is_valid_operand(int operand) {
    if (operand < 0 || operand > MAX_OPERAND) {
        return 0; // Invalid operand
    }
    return 1; // Valid operand
}

// Function to process the job (list of instructions and operands)
void process_job(const char instructions[][10], int operands[], int num_instructions) {
    for (int i = 0; i < num_instructions; i++) {
        printf("Processing instruction: %s %d\n", instructions[i], operands[i]);
        
        // Check if the opcode is valid
        if (!is_valid_opcode(instructions[i])) {
            raise_interrupt("Invalid opcode encountered!");
        }
        
        // Check if the operand is valid
        if (!is_valid_operand(operands[i])) {
            raise_interrupt("Invalid operand encountered!");
        }
    }
    printf("All instructions processed successfully.\n");
}

int main() {
    int num_instructions;
    
    // Ask the user for the number of instructions
    printf("Enter the number of instructions: ");
    scanf("%d", &num_instructions);

    // Arrays to store instructions and operands
    char instructions[num_instructions][10];
    int operands[num_instructions];
    
    // Take input instructions and operands from the user
    printf("Enter the instructions and operands (e.g., LOAD 25):\n");
    for (int i = 0; i < num_instructions; i++) {
        scanf("%s %d", instructions[i], &operands[i]);
    }
    
    // Process the job and check for opcode and operand errors
    process_job(instructions, operands, num_instructions);
    
    return 0;
}



// Enter the number of instructions: 3
// Enter the instructions and operands (e.g., LOAD 25):
// LOAD 20
// ADD 10
// STORE 50



/*

The code simulates a basic instruction processing system, where each instruction consists of an opcode (such as LOAD, ADD, SUB, etc.) 
and an operand (a numeric value that accompanies the opcode). 
The goal of the program is to check if each opcode is valid and if the operand is within an acceptable range (0 to 100). 
If any instruction contains an invalid opcode or operand, the program raises an "interrupt" (simulated error) and exits.

MAX_OPCODES: Specifies the maximum number of valid opcodes (5 in this case: LOAD, ADD, SUB, STORE, JMP).
MAX_OPERAND: Defines the range for valid operands (0 to 100). If an operand is outside this range, it is considered invalid.

This function simulates an interrupt (an error in the system) by printing an error message and terminating the program with exit(1). 
This is invoked whenever an invalid opcode or operand is encountered.


Function is_valid_opcode():
This function checks if a given opcode is valid.
It compares the provided opcode with the valid opcodes (LOAD, ADD, SUB, STORE, JMP) using strcmp().
If a match is found, it returns 1 (valid opcode). If no match is found, it returns 0 (invalid opcode).

unction is_valid_operand():
This function checks if the operand is within the valid range (0 to 100).
If the operand is outside this range, it returns 0 (invalid operand). Otherwise, it returns 1 (valid operand).
Function process_job():

This function processes each instruction (opcode and operand) in a loop.
It prints each instruction as it is being processed.
It checks whether the opcode is valid using is_valid_opcode().
It checks whether the operand is valid using is_valid_operand().
If either the opcode or operand is invalid, it raises an interrupt by calling raise_interrupt().
If all instructions are valid, the function prints "All instructions processed successfully.".

The program first asks the user for the number of instructions.
It then dynamically creates two arrays: instructions[] for the opcodes and operands[] for the operand values, based on the number of instructions entered.
The program prompts the user to input the opcode and operand for each instruction.
It calls the process_job() function to process the instructions, check for errors, and print the result.
Overall Program Flow:
The user enters the number of instructions.
The user enters the instructions and operands.
The program processes each instruction:
Checks if the opcode is valid (matches one of LOAD, ADD, SUB, STORE, JMP).
Checks if the operand is valid (within the range 0-100).
If all instructions are valid, the program prints a success message.
If any instruction has an invalid opcode or operand, the program raises an interrupt and terminates.


*/