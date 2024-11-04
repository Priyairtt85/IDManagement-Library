#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include<avl_api.h>
#include<hash_api.h>

int main()
{
  struct Node *root = NULL;
  int i;
  int id;
  struct Node *result;

  HashTable_t *table = malloc(sizeof(HashTable_t));

  /* Unit test case for insert_id */

  printf("\nCreate id for abcassa started \n");
  root = create_id(root,"abcassa",table);
  printf("\nCreate id for abcassa started\n");
  root = create_id(root,"abcassa",table);
  printf("\nCreate id for kljkl started\n");
  root = create_id(root,"kljkl",table);
  printf("\nCreate id for abcassa started\n");
  root = create_id(root,"abcassa",table);
  printf("\nCreate id for kljkl started\n");
  root = create_id(root,"kljkl",table);

/* Uni test case for tree traversal */
  printf("\nPreorder traversal of the constructed AVL tree is \n");
  preOrder(root);
/* Unit test for Query ID for the database */
  printf("\nSearch for 4049526272 \n");
  result = search(root, 4049526272);
  if (result != NULL)
      printf("ID exists : %u\n", result->key);
  else
      printf("ID 4049526272 Not Found\n");

  printf("\nSearch for 895317504 \n");
  result = search(root, 895317504);
  if (result != NULL)
      printf("ID exists : %u\n", result->key);
  else
      printf("ID 895317504 Not Found\n");

  printf("\n 1 Preorder traversal of the constructed AVL tree is \n");
  preOrder(root);

  printf("\n 1 Preorder traversal of the constructed AVL tree is \n");
  preOrder(root);

/* Unit test for delete ID for the database */
  printf("\nDelete the ID - 4049526272 \n");
  result = delete_id(root, 4049526272);
  if (result != NULL)
      printf("Deleted the id : %u\n", result->key);
  else
      printf("ID 4049526272 not found to delete\n");


  printf("\n 2 Preorder traversal of the constructed AVL tree is \n");
  preOrder(root);

  printf("\nSearch for 4049526272 \n");
  result = search(root, 4049526272);
  if (result != NULL)
    printf("ID exists : %u\n", result->key);
  else
    printf("ID 4049526272 Not Found\n");

  printf("\nSearch for 4049526272 \n");
  result = search(root, 4049526272);
  if (result != NULL)
      printf("ID exists : %u\n", result->key);
  else
      printf("ID 4049526272 Not Found\n");

  printf("\nSearch for 895317504 \n");
  result = search(root, 895317504);
  if (result != NULL)
      printf("ID exists : %u\n", result->key);
  else
      printf("ID 895317504 Not Found\n");

  printf("\nPreorder traversal of the constructed AVL tree is \n");
  preOrder(root);

  printf("\nCreate id for abcassa started \n");
  root = create_id(root,"abcassa",table);
  printf("\nPreorder traversal of the constructed AVL tree is \n");
  preOrder(root);

  printf("\nSearch for 4049526272 \n");
  result = search(root, 4049526272);
  if (result != NULL)
      printf("ID exists : %u\n", result->key);
  else
      printf("ID 4049526272 Not Found\n");

  printf("\nSearch for 4049526273 \n");
  result = search(root, 4049526273);
  if (result != NULL)
      printf("ID exists : %u\n", result->key);
  else
      printf("ID 4049526273 Not Found\n");

  printf("\nSearch for 895317504 \n");
  result = search(root, 895317504);
  if (result != NULL)
      printf("ID exists : %u\n", result->key);
  else
      printf("ID 895317504 Not Found\n");

  printf("\nCreate id for abcassa started \n");
  root = create_id(root,"abcassa",table);
  printf("\nCreate id for kljkl started \n");
  root = create_id(root,"kljkl",table);
  
  printf("\nPreorder traversal of the constructed AVL tree is \n");
  preOrder(root);

/* Unit test for cleanup inactive IDs in the database */

  printf("\nAVL Tree cleanup started\n");
  preOrder_cleanup(root,root);
  printf("\nAVL Tree cleanup completed\n");

  printf("\nPreorder traversal of the constructed AVL tree is \n");
  preOrder(root);

  return 0;

}
