#ifndef __HASHAPI_H__
#define __HASHAPI_H__

#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
//#include <avl_api.h>

//Hash table size

#define TABLE_SIZE 100

// Structure for key-value pair
typedef struct Entry {
    char* key;
    uint32_t value;
    int duplicate_count;
} Entry_t;

// Structure for hash table
typedef struct HashTable{
    Entry_t* entries[TABLE_SIZE];
} HashTable_t;

extern unsigned int hash(char* key);

extern HashTable_t* createHashTable();

extern void insertHash(HashTable_t* ht, char* key, uint32_t value);

extern int getHash(HashTable_t* ht, char* key);

extern int getHashDuplicateCount(HashTable_t* ht, char* key);

extern void updateHash(HashTable_t *ht, char *key, uint32_t value, int duplicate_count);

#endif /* __HASHAPI_H__ */
