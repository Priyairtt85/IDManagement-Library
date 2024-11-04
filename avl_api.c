#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include<avl_api.h>
#include<hash_api.h>


// A utility function to get height of the tree
int height(struct Node *N)
{
  if (N == NULL)
    return 0;
  return N->height;
}

// A utility function to get maximum of two integers
int max(int a, int b)
{
  return (a > b)? a : b;
}

/* Helper function that allocates a new node with the given key and
    NULL left and right pointers. */
struct Node* newNode(uint32_t key)
{
  struct Node* node = (struct Node*) malloc(sizeof(struct Node));
  node->key = key;
  node->isactive=1;
  node->left = NULL;
  node->right = NULL;
  node->height = 1; // new node is initially added at leaf
  return(node);
}

// A utility function to right rotate subtree rooted with y
struct Node *rightRotate(struct Node *y)
{
  struct Node *x = y->left;
  struct Node *T2 = x->right;
  // Perform rotation
  x->right = y;
  y->left = T2;

  // Update heights
  y->height = max(height(y->left), height(y->right))+1;
  x->height = max(height(x->left), height(x->right))+1;

  // Return new root
  return x;
}

// A utility function to left rotate subtree rooted with x
struct Node *leftRotate(struct Node *x)
{
  struct Node *y = x->right;
  struct Node *T2 = y->left;

  // Perform rotation
  y->left = x;
  x->right = T2;

  //  Update heights
  x->height = max(height(x->left), height(x->right))+1;
  y->height = max(height(y->left), height(y->right))+1;

  // Return new root
  return y;
}

// Get Balance factor of node N
int getBalance(struct Node *N)
{
  if (N == NULL)
    return 0;
  return height(N->left) - height(N->right);
}



struct Node* insert_id(struct Node* node, uint32_t key, HashTable_t *ht)
{
  /* 1.  Perform the normal BST rotation */

  if (node == NULL)
    return(newNode(key));

  if (key < node->key)
     node->left = insert_id(node->left, key, ht);
  else if (key > node->key)
      node->right = insert_id(node->right, key, ht);
  else // Equal keys not allowed
      return node;

  /* 2. Update height of this ancestor node */
  node->height = 1 + max(height(node->left),
                        height(node->right));

  /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
  int balance = getBalance(node);

  // If this node becomes unbalanced, then there are 4 cases

  // Left Left Case
  if (balance > 1 && key < node->left->key)
      return rightRotate(node);

  // Right Right Case
  if (balance < -1 && key > node->right->key)
      return leftRotate(node);

  // Left Right Case
  if (balance > 1 && key > node->left->key)
  {
      node->left = leftRotate(node->left);
      return rightRotate(node);
  }

  if (balance < -1 && key < node->right->key)
  {
      node->right = rightRotate(node->right);
      return leftRotate(node);
  }

  /* return the (unchanged) node pointer */
  return node;
}

/* Given a non-empty binary search tree, return the
   node with minimum key value found in that tree.
   Note that the entire tree does not need to be
   searched. */
struct Node * minValueNode(struct Node* node)
{
    struct Node* current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
      current = current->left;

    return current;
}

// Recursive function to delete a node with given key
// from subtree with given root. It returns root of
// the modified subtree.
struct Node* deleteNode(struct Node* root, uint32_t key)
{
  // STEP 1: PERFORM STANDARD BST DELETE
  if (root == NULL)
    return root;

  // If the key to be deleted is smaller than the
  // root's key, then it lies in left subtree
  if ( key < root->key )
      root->left = deleteNode(root->left, key);

  // If the key to be deleted is greater than the
  // root's key, then it lies in right subtree
  else if( key > root->key )
    root->right = deleteNode(root->right, key);

  // if key is same as root's key, then This is
  // the node to be deleted
  else
  {
  // node with only one child or no child
    if( (root->left == NULL) || (root->right == NULL) )
    {
      struct Node *temp = root->left ? root->left : root->right;

      // No child case
      if (temp == NULL)
      {
        temp = root;
        root = NULL;
      }
      else // One child case
        *root = *temp; // Copy the contents of
                      // the non-empty child
      free(temp);
    }
    else
    {
        // node with two children: Get the inorder
        // successor (smallest in the right subtree)
        struct Node* temp = minValueNode(root->right);

        // Copy the inorder successor's data to this node
        root->key = temp->key;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->key);
    }
  }

  // If the tree had only one node then return
  if (root == NULL)
      return root;

  // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(height(root->left), height(root->right));

  // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
  // check whether this node became unbalanced)
  int balance = getBalance(root);

  // If this node becomes unbalanced, then there are 4 cases

  // Left Left Case
  if (balance > 1 && getBalance(root->left) >= 0)
      return rightRotate(root);

  // Left Right Case
  if (balance > 1 && getBalance(root->left) < 0)
  {
    root->left = leftRotate(root->left);
        return rightRotate(root);
  }

  // Right Right Case
  if (balance < -1 && getBalance(root->right) <= 0)
    return leftRotate(root);

  // Right Left Case
  if (balance < -1 && getBalance(root->right) > 0)
  {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}

struct Node *search(struct Node *root, uint32_t key) {
  if (root == NULL)
    return root;

  if (root->key == key)
      if (root->isactive == 1)
        return root;
      else
        return NULL;
  if (key < root->key)
      return search(root->left, key);

  return search(root->right, key);
}

struct Node *delete_id(struct Node *root, uint32_t key) {
  if (root == NULL) {
    return root;
  }
  // Find the node to update
  if (key < root->key) {
    delete_id(root->left, key);
  } else if (key > root->key) {
    delete_id(root->right, key);
  } else if (root->key == key){
      root->isactive=0;
      return root;
  }

}
// A utility function to print preorder traversal of
// the tree.

void preOrder(struct Node *root)
{
  if(root != NULL)
  {
    printf("%u ", root->key);
    preOrder(root->left);
    preOrder(root->right);
  }
}

// A utility function to cleanup the inactive nodes in the tree
// with preorder traversal 
void preOrder_cleanup(struct Node *root,struct Node *node)
{
    if(node != NULL) {
      // Perform deletion here if needed
      if (node->isactive==0) {
          node = deleteNode(root, node->key);
          root = node;
      }

      if (node != NULL) {
        preOrder_cleanup(root,node->left);
        preOrder_cleanup(root,node->right);
      }
  }
}

//A Utility function to generate 32 bit hash key with duplicate handling
uint32_t generate_id(char* key,int duplicate_count) {

  uint32_t hash = 0;
  const uint8_t *bytes = (const uint8_t*)key;
  int len = sizeof(key);
  for (int i = 0; i < len; i++) {
      hash = (hash * 31) + bytes[i];
  }

  uint32_t hash32 = hash & 0xFFFFFF;
  return (hash32<<8) | duplicate_count; // return newhash32;

}

// A Utility function to create a new node with the given key
struct Node* create_id(struct Node* node, char *key, HashTable_t *ht) {
    uint32_t key_hash=getHash(ht,key);
    if (key_hash == -1){
        key_hash=generate_id(key,0);
        insertHash(ht, key, key_hash);
        printf("\nGenerated id for the key %s : %u\n", key,getHash(ht, key));
        return insert_id(node, key_hash, ht);
    }
    else {
        struct Node *result = search(node, key_hash);
        if (result != NULL){
            printf("\nID Already exists : %u\n", result->key);
            return node;
        } else {
            int DuplicateCount=getHashDuplicateCount(ht,key) + 1;
            key_hash=generate_id(key,DuplicateCount);
            updateHash(ht, key, key_hash, DuplicateCount);
            printf("\nGenerated id for the key %s : %u\n", key,getHash(ht, key));
            return insert_id(node, key_hash, ht);
        }
    }
}

