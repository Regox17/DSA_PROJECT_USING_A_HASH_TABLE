#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
// Define the table size
#define SIZE 25 
#define TABLE_SIZE 50

// Symbol structure

typedef struct {
    char name[50];
    char symbol_type[50];
    char data_type[50];
    char scope[50];
    char value[50];
    char memory_location[50];
    char remarks[100];
} Symbol;

// Hash table structure
typedef struct {
    Symbol table[TABLE_SIZE];  // Array of Symbol structures
    int is_occupied[TABLE_SIZE]; // Array to track occupied slots
} HashTable;

// Function declarations
int hashFunction(char* symbol);
void initHashTable(HashTable* ht);
void insert(HashTable* ht, Symbol symbol);
void readTextFileAndInsert(HashTable* ht, const char* filename);
void display(HashTable* ht);
void checkErrors(HashTable* ht);
