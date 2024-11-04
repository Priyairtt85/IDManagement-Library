#ifndef __AVLAPI_H__
#define _AVLAPI_H__
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <hash_api.h>

struct Node
{
    uint32_t key;
    int isactive;
    struct Node *left;
    struct Node *right;
    int height;
};


    
// A utility function to get maximum of two integers
extern int max(int a, int b);

// A utility function to get height of the tree
extern int height(struct Node *N);
extern struct Node* newNode(uint32_t key);
extern struct Node *rightRotate(struct Node *y);
extern struct Node *leftRotate(struct Node *x);
extern int getBalance(struct Node *N);
extern struct Node* insert_id(struct Node* node, uint32_t key, HashTable_t *ht);
extern struct Node * minValueNode(struct Node* node);
extern struct Node* deleteNode(struct Node* root, uint32_t key);
extern struct Node *search(struct Node *root, uint32_t key);
extern struct Node *delete_id(struct Node *root, uint32_t key);
extern void preOrder(struct Node *root);
extern void preOrder_cleanup(struct Node *root,struct Node *node);
extern uint32_t generate_id(char* key,int duplicate_count);
extern struct Node* create_id(struct Node* node, char *key, HashTable_t *ht);

#endif /* __AVLAPI_H__ */
