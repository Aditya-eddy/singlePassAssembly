# Simple Assembler

This project is a simple assembler for a hypothetical assembly language. It reads assembly code from an input file, parses it, and outputs the corresponding machine code.

## Features

- Parses labels, mnemonics, and operands from assembly code.
- Supports a predefined set of opcodes.
- Generates machine code for each instruction.
- Maintains a symbol table for labels.

## Opcode Table

The assembler supports the following mnemonics and their corresponding opcodes and sizes:

| Mnemonic | Opcode | Size |
|----------|--------|------|
| MOV      | 1      | 1    |
| ADD      | 2      | 1    |
| SUB      | 3      | 1    |
| MUL      | 4      | 1    |
| DIV      | 5      | 1    |
| LOAD     | 6      | 1    |
| STORE    | 7      | 1    |
| JMP      | 8      | 1    |
| JNZ      | 9      | 1    |
| HALT     | 10     | 1    |

## File Structure

- `assembler.c`: The main assembler source code file.
- `input.asm`: The input file containing the assembly code to be assembled.

## Usage

1. Compile the assembler:

    ```sh
    gcc -o assembler assembler.c
    ```

2. Create an input file `input.asm` with your assembly code. Example content:

    ```asm
    START:  MOV A
            ADD B
            JMP START
            HALT
    ```

3. Run the assembler:

    ```sh
    ./assembler
    ```

4. The output will be the machine code printed to the console.

## Example

Given the following `input.asm` file:

```asm
START:  MOV A
        ADD B
        JMP START
        HALT



