#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include<avl_api.h>
#include<hash_api.h>
#include <signal.h>
#include <getopt.h>
#include <ctype.h>

#define PARSE_SUCCESS 0
#define PARSE_ERROR     (!PARSE_SUCCESS)
#define NAME_SZ         256
#define KEY_SZ          32

static int      create_id_opt = 0;
static int      delete_id_opt = 0;
static int      query_id_opt = 0;
static int      show_db_opt = 0;
static char    name[NAME_SZ];
static uint32_t    keyID = 0;

struct Node *root = NULL;

static void
idmgmt_usage(void)
{
        fprintf(stdout, "idmgmt Usage:\n"
                        "Enter h - \tDisplays the usage of the ID Management app\n"
                        "Enter c - \tCreate the ID to the database\n"
                        "Enter d - \tDelete the ID from the database\n"
                       "Enter q - \tSearch for the ID from the database\n"
                        "Enter s - \tShow the nodes in the database\n"
                        "Enter r - \t Release inactive nodes in the database\n"
                        "Enter e - \tExit the program\n");
}


int main(int argc, char *argv[])
{
  //struct Node *root = NULL;
  int i;
  int id;
  int ret = 0;
  struct Node *result;
  int ch;
  int c;

  HashTable_t *table = malloc(sizeof(HashTable_t));

  idmgmt_usage();


        while (1) {
                printf("\nEnter the option: ");
                ch = tolower(getchar());

                if (ch == 'c') {
                        printf("Enter the name to add in the library: ");
                        while (( c= getchar()) != '\n' && c != EOF);
                        fgets(name, sizeof(name), stdin);
                        printf ("Entered value %s\n", name);
                        root = create_id(root,name,table);
                } else if (ch == 'd') {
                        printf("Enter the ID to be deleted in the library: ");
                        scanf("%d", &keyID);
                        result = delete_id(root,keyID);
                        if (result != NULL)
                                printf("Deleted the id : %u\n", result->key);
                        else
                                printf("ID %u not found to delete\n", keyID);
                        while (( c= getchar()) != '\n' && c != EOF);
                } else if (ch == 'q') {
                        printf("Enter the ID to be searched in the library: ");
                        scanf("%d", &keyID);
                        result = search(root, keyID);
                        if (result != NULL)
                                printf("ID exists : %u\n", result->key);
                        else
                                printf("ID %u Not Found\n", keyID);
                        while (( c= getchar()) != '\n' && c != EOF);
                } else if (ch == 's') {
                        printf("Printing all the IDs in the library\n");
                        preOrder(root);
                        while (( c= getchar()) != '\n' && c != EOF);
                } else if (ch == 'r') {
                        printf("Releasing the inactive nodes in the library - started\n");
                        preOrder_cleanup(root,root);
                        printf("Releasing the inactive nodes in the library - completed\n");
                        while (( c= getchar()) != '\n' && c != EOF);
                } else if (ch == 'e') {
                        printf("Exiting from the application\n");
                        return (0);
                } else if (ch != '\n') {
                        printf ("Invalid options. Please enter the correct option from the menu\n");
                        idmgmt_usage();
                        while (( c= getchar()) != '\n' && c != EOF);
                }
        }
    return (0);
}
                                                                                                   
                                                                           
