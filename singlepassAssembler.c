#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LABELS 100
#define MAX_LABEL_LEN 20
#define MAX_LINE_LEN 100

// Structure for symbol table entries
typedef struct {
    char label[MAX_LABEL_LEN];
    int address;
} Symbol;

// Structure for opcode table entries
typedef struct {
    char mnemonic[10];
    int opcode;
    int size;
} Opcode;

// Example opcode table
Opcode opcodes[] = {
    {"MOV", 1, 1}, {"ADD", 2, 1}, {"SUB", 3, 1},
    {"MUL", 4, 1}, {"DIV", 5, 1}, {"LOAD", 6, 1},
    {"STORE", 7, 1}, {"JMP", 8, 1}, {"JNZ", 9, 1},
    {"HALT", 10, 1}
};

int findOpcode(char *mnemonic) {
    for (int i = 0; i < sizeof(opcodes) / sizeof(opcodes[0]); i++) {
        if (strcmp(opcodes[i].mnemonic, mnemonic) == 0) {
            return i;
        }
    }
    return -1; // Not found
}

int main() {
    FILE *inputFile;
    char line[MAX_LINE_LEN];
    Symbol symbolTable[MAX_LABELS];
    int symbolCount = 0;
    int locationCounter = 0;
    int lineCount = 0;

    // Open input file
    inputFile = fopen("input.asm", "r");
    if (inputFile == NULL) {
        printf("Error: Could not open input file.\n");
        return 1;
    }

    // Read each line of the input file
    while (fgets(line, sizeof(line), inputFile) != NULL) {
        char label[MAX_LABEL_LEN] = {0}, mnemonic[10] = {0}, operand[20] = {0};
        int opcodeIndex;

        // Remove newline character
        line[strcspn(line, "\n")] = '\0';

        // Skip empty lines
        if (strlen(line) == 0) {
            continue;
        }

        // Check if the line contains a label
        char *colon = strchr(line, ':');
        if (colon) {
            // Extract label
            *colon = '\0';
            strcpy(label, line);
            strcpy(line, colon + 1);

            // Remove leading whitespace from the rest of the line
            char *trimmed_line = line;
            while (isspace((unsigned char)*trimmed_line)) trimmed_line++;

            // Add label to symbol table
            strcpy(symbolTable[symbolCount].label, label);
            symbolTable[symbolCount].address = locationCounter;
            symbolCount++;

            // Replace line with trimmed line
            strcpy(line, trimmed_line);
        }

        // Skip data declarations
        if (sscanf(line, "%s %s", mnemonic, operand) < 2 && isdigit((unsigned char)line[0])) {
            continue;
        }

        // Parse mnemonic and operand
        int fields = sscanf(line, "%s %s", mnemonic, operand);

        // Find the opcode
        opcodeIndex = findOpcode(mnemonic);
        if (opcodeIndex == -1) {
            printf("Error: Unknown mnemonic '%s' on line %d\n", mnemonic, lineCount + 1);
            return 1;
        }

        // Print the machine code
        if (fields == 2) {
            printf("%04d: %02d %s\n", locationCounter, opcodes[opcodeIndex].opcode, operand);
        } else {
            printf("%04d: %02d\n", locationCounter, opcodes[opcodeIndex].opcode);
        }

        // Update the location counter
        locationCounter += opcodes[opcodeIndex].size;
        lineCount++;
    }

    fclose(inputFile);
    return 0;
}
