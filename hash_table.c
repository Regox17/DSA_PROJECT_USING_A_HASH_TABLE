#include "hash_table.h"

// Hash function to calculate the hash value
int hashFunction(char* symbol) {
    int hash = 0;
    for (int i = 0; symbol[i] != '\0'; i++) {         //SUMING UP ALL THE CHARACTER ASCII VALUE 
        hash = (hash + symbol[i]) % TABLE_SIZE;       // USING MOD TO EXTRACT INDEX POSITION
    }
    return hash;
}

// Initialize the hash table
void initHashTable(HashTable* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->is_occupied[i] = 0;
    }
}

// Insert a symbol into the hash table
void insert(HashTable* ht, Symbol symbol) {
    int index = hashFunction(symbol.name);
    int temp=index;
    // Linear probing in case of collisions
    while (ht->is_occupied[index]) {
        if ((index + 1) % TABLE_SIZE == temp) {
            printf("Hash table is full, cannot insert new symbol.\n");
            return;                                     // Table is full, we cannot insert
        } 
        index = (index + 1) % TABLE_SIZE;
    }

    ht->table[index] = symbol;
    ht->is_occupied[index] = 1;
}

// Read a text file and insert symbols into the hash table
void readTextFileAndInsert(HashTable* ht, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", filename);
        return;
    }

    Symbol symbol;
    char line[300]; //buffer to store data 

    // Skip the header row
    fgets(line, sizeof(line), file);
    
    // Read each line and parse the data
    while (!feof(file) && fgets(line, sizeof(line), file) ) {
        sscanf(line, "%49s %49s %49s %49s %49[^\t] %49s %[^\n]",
               symbol.name, symbol.symbol_type, symbol.data_type, 
               symbol.scope, symbol.value, symbol.memory_location, symbol.remarks);
        insert(ht, symbol);
    }

    fclose(file);
}

// Display the contents of the hash table
void display(HashTable* ht) {
    // Header for the table
    printf("Index | %-20s | %-15s | %-10s | %-30s | %-20s | %-15s | %-20s\n", 
           "Name", "Symbol_Type", "Data_Type", "Scope", "Value", "Memory_Location", "Remarks");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (ht->is_occupied[i]) {
            // Print data for occupied slots
            printf("%-5d | %-20s | %-15s | %-10s | %-30s | %-20s | %-15s | %-20s\n", 
                   i,
                   ht->table[i].name, ht->table[i].symbol_type, ht->table[i].data_type,
                   ht->table[i].scope, ht->table[i].value, ht->table[i].memory_location,
                   ht->table[i].remarks);
        } else {
            // Print placeholder for empty slots
            printf("%-5d | %-20s | %-15s | %-10s | %-30s | %-20s | %-15s | %-20s\n", 
                   i, "NULL ", "NULL ", "NULL ", "NULL ", "NULL ", "NULL ", "NULL ");
        }
    }
}

// Check for errors in the hash table
void checkErrors(HashTable* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (ht->is_occupied[i]) {
            // Check for undeclared identifiers
            if (strcmp(ht->table[i].data_type, "Unknown") == 0) {
                printf("\t\tError: Undeclared identifier found: %s\n", ht->table[i].name);
                ht->is_occupied[i] = 0; // Remove the entry by marking it unoccupied
                continue;
            }

            // Check for type mismatches for "int"
            if (strcmp(ht->table[i].data_type, "int") == 0) {
                if (strcmp(ht->table[i].value, "Unknown") == 0) {
                    continue;
                }

                int isNum = 1;  // Assume the value is numeric
                int isArray = 0; // Flag to indicate if this is an array

                // Check if the value contains commas or spaces (array-like value)
                for (int index = 0; ht->table[i].value[index] != '\0'; index++) {
                    char currentChar = ht->table[i].value[index];
                    if (currentChar == ',' || currentChar == ' ') {
                        isArray = 1; // Allow commas/spaces for array elements
                    } else if (currentChar < '0' || currentChar > '9') {
                        isNum = 0;
                        break;
                    }
                }

                if (isArray) {
                    // Treat as a valid array of integers
                    char valueCopy[50];
                    strcpy(valueCopy, ht->table[i].value);
                    char* token = strtok(valueCopy, ", ");

                    while (token != NULL) {
                        for (int k = 0; token[k] != '\0'; k++) {
                            if (token[k] < '0' || token[k] > '9') {
                                isNum = 0;
                                break;
                            }
                        }
                        if (!isNum) break;
                        token = strtok(NULL, ", ");
                    }
                }

                if (!isNum && !isArray) {
                    printf("\t\tError: Type mismatch for identifier: %s\n", ht->table[i].name);
                    ht->is_occupied[i] = 0; // Remove the entry by marking it unoccupied
                    continue;
                }
            }

            // Check for type mismatches for "bool"
            if (strcmp(ht->table[i].data_type, "bool") == 0) {
                if (strcmp(ht->table[i].value, "Unknown") == 0) {
                    continue;
                }
                if (strcmp(ht->table[i].value, "true") != 0 && strcmp(ht->table[i].value, "false") != 0) {
                    printf("\t\tError: Type mismatch for identifier: %s\n", ht->table[i].name);
                    ht->is_occupied[i] = 0; // Remove the entry by marking it unoccupied
                    continue;
                }
            }

            // Check for duplicate declarations
            for (int j = i + 1; j < TABLE_SIZE; j++) {
                if (ht->is_occupied[j] && strcmp(ht->table[i].name, ht->table[j].name) == 0) {
                    printf("\t\tError: Multiple declarations of identifier: %s\n", ht->table[i].name);
                    ht->is_occupied[j] = 0; // Remove the duplicate entry
                }
            }
        }
    }
}

