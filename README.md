# Hash Table Implementation in C

This project implements a **hash table** data structure in **C** as part of a **Data Structures and Algorithms (DSA)** course. The hash table supports operations like **insertion**, **collision handling**, and **error checking**.

## Features

- **Hash Function**: Calculates hash values for symbols based on their ASCII values.
- **Collision Handling**: Implements **linear probing** to resolve collisions.
- **Error Checking**: Identifies undeclared identifiers, type mismatches, and duplicate declarations.
- **File Handling**: Reads data from a text file and inserts symbols into the hash table.
- **Display**: Displays the contents of the hash table in a user-friendly table format.

## Files

- `hash_table.c`: Contains the implementation of the hash table.
- `hash_table.h`: Header file with the data structure and function prototypes.
- `report.pdf`: Detailed project report (Add this file if you have it).

## Compilation and Execution

1. **To compile the program**:
   ```bash
   gcc hash_table.c -o hash_table
