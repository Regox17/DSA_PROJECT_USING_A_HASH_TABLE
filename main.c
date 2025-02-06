#include "hash_table.h"

// Main function
int main() {
    HashTable ht;
    initHashTable(&ht);

    const char* filename = "variable_data.txt"; // Input file name

    clock_t start, end; // Variables to measure time

    // 1. Measure time for reading file and inserting symbols
    printf("\n\t\t\t\t\t\t\e[1mPERFORMING READ OPERATION\e[m\n\n");
    start = clock();
    readTextFileAndInsert(&ht, filename);
    end = clock();
    printf("\nTime taken to read file and insert symbols: %f seconds\n\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Display the symbol table
    printf("\t\t\t\t\t\t\t\e[1mSYMBOL TABLE\e[m\n\n");
    display(&ht);

    // 2. Measure time for error checking
    printf("\n\t\t\t\t\t\t\e[1mPERFORMING ERROR CHECK\e[m\n\n");
    start = clock();
    checkErrors(&ht);
    end = clock();
    printf("\n\nTime taken for error checks: %f seconds\n\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Display the symbol table after error checking
    printf("\n\t\t\t\t\t\t\e[1mSYMBOL TABLE\e[m (After Error Checking)\n\n");
    display(&ht);
    return 0;
}
