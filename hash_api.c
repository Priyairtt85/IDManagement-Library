#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <hash_api.h>
//#include <avl_api.h>

// Hash function
unsigned int hash(char* key) {
    unsigned int hashval = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hashval = hashval * 31 + key[i];
    }
    return hashval % TABLE_SIZE;
}

// Create a new hash table
HashTable_t* createHashTable() {
    HashTable_t* ht = (HashTable_t*)malloc(sizeof(HashTable_t));
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->entries[i] = NULL;
    }
    return ht;
}

// Insert a key-value pair into the hash table
void insertHash(HashTable_t* ht, char* key, uint32_t value) {
    unsigned int index = hash(key);

    Entry_t* newEntry = (Entry_t*)malloc(sizeof(Entry_t));
    newEntry->key = strdup(key);
    newEntry->value = value;
    newEntry->duplicate_count = 0;

    ht->entries[index] = newEntry;
}

// Get a value from the hash table
int getHash(HashTable_t* ht, char* key) {
    unsigned int index = hash(key);

    if (ht->entries[index] != NULL) {
        return ht->entries[index]->value;
    } else {
        return -1; // Key not found
    }
}

// Get a Duplicate count entry's value from the hash table
int getHashDuplicateCount(HashTable_t* ht, char* key) {
    unsigned int index = hash(key);

    if (ht->entries[index] != NULL) {
        return ht->entries[index]->duplicate_count;
    } else {
        return -1; // Key not found
    }
}

void updateHash(HashTable_t *ht, char *key, uint32_t value, int duplicate_count) {
    unsigned int index = hash(key);

    if (ht->entries[index] != NULL) {
       if (strcmp(ht->entries[index]->key, key) == 0) {
            ht->entries[index]->value = value;
            ht->entries[index]->duplicate_count = duplicate_count;
            return;
        }
    }
}
