**ID Management Library**
========================

This is a standalone library/binary with user interface, which can be used to store 32 bit ID database. 
It has all the support such as create, delete, query and show the current database functionality. Even it can handle duplicate entries for recently deleted logical ID's and delete them 
permantely as part of cleanup.

**Description**
===============

ID management application has been implemented with 32bit unique hash ID based on the input string, which is used as the key in the AVL tree data structure.
Based on the design requirement, proceed in implementing the application using AVL tree because of its benefits such as :
- In-memory DB for faster computation time and higher performance, rather than external file based DB such as SQLite DB, which might have performance issues
  with large DB with file system limitations and also SQLlite as it doesnt support inbuilt encryption so the data is potentialy vulnerable.
- Efficient in search, insert, and delete operations: AVL trees have a guaranteed O(log n) time complexity for these operations. 
This is because the tree's height is always logarithmic in the number of node.
- AVL trees are always height-balanced, which ensures efficient operations.

**Handling for Logically deleted entries** :
----------------------------------------

Apart from this, the 32 bit hash ID also able to accommodate the duplicate entries for the recently logically deleted but not physically deleted from the database. 
To keep track of these logically deleted entries in the DB and provide next unique ID for the same input string was implemented by using the "**is_active**" field 
in the AVL tree's node structure. By default all the new entry will have this field set to "1", but if incase a node is deleted by user this field will be set to "0", so in the next
query for same ID it will throw an error as "ID not found", as the query operation display only the active node members, but if incase for same ID a create operation is performed 
then it will be provide the next unique ID, which is explained in below logic.

**Handling duplicate entries for logically deleted entries**:
-------------------------------------------------------------

This was achieved by reserving last 8 bits of 32bit ID for accomdating the duplicate key IDs if the previously created ones are not physically deleted from the database. 
Hence, 24 bit of the input string hash value has been used along with 8-bit reservation for duplicate entries and the new hash value will be derived based on this calculation.
The Hash node strucure has duplicate_count memeber which will keep track of duplicate entries for the given input string by incrementing from its previous value.

32 bit hash key ID --- 24 bit hash value from Input string + 8-bit for duplicate entries for recently logically deleted entries from the DB

**Cleanup function handling for logically deleted entries :**
-----------------------------------------------------------
These logically deleted entries (is_active set to "0") will be deleted permanantely/physically through the cleanup task. 
 Currently the cleanup task was included as part of an input parameter from the user, but this can be modified by scheduling the background process which will delete all the is_Active
   set to '0' nodes in the AVL tree structure.

As mentioned earlier, the ID management application includes all the DB related operations with AVL tree datastructure such as:
 - Create a new entry by providing the arbitary string as input to the ID management library using **"create_id"**() API. If an already existing ID is created again without deletion, it will throw
   an error "ID already exists", but if incase the create ID was performed again for the same key ID after recent logical deletion, then the generate_id() API will provide the subsequent
   unique 32bit hash key (as mentioned under the section :- Handling duplicate entries for logically deleted entries*).
 - Delete an existing entry with unique 32-bit key ID using the **"delete_id"**() API. If the key ID is not present in the DB, error will be returned as - "ID not found".
 - Query an existing entry with unique 32-bit key ID using the **"search_id"()** API, if the key ID is not present or for invalid key ID, an error will be returned as "ID not found".
 - Show the current database/node contents was performed using the preOrder tree traversal of AVL tree nodes.
 - If any other invalid options is provided by user, it will throw usage error and prompt the user for correct input option.
 - Help option will list usage of the application to the user.
 - Release option - Cleanup the logically deleted entries from the DB permanently using **"preOrder_cleanup"**() API.

**Getting Started**:
===================
There is no external dependecies/libraries required for the binary, as implemented the AVL tree insertion, deletion, search and tree rotation for height balanced in the avl_api.c file .

Code structure:
--------------
 - hash_api.c and .h files-- Contains the hash related operations and its functionality
 - avl_api.c and .h files -- Containst the AVL tree data structure operations
- id_mgmt_app.c -- Main function which has the user interface for the ID management library
- unittest_id_mgmt.c -- Contains the unit test code for the ID management operations such as create, delete, search, traversal and cleanup operations.

**Installing and Executing program**:
-----------------------------------
- Execute the makefile using command "make" which will provide the binary files for the actual application (id_mgmt_app) and unit test code(unittest_id_mgmt).
  
~/IDManagement-Library$ ./idMgmt 


idmgmt Usage:

Enter h -   Displays the usage of the ID Management app 

Enter c -   Create the ID to the database

Enter d -   Delete the ID from the database

Enter q -   Search for the ID from the database

Enter s -   Show the nodes in the database

Enter r -    Release inactive nodes in the database

Enter e -   Exit the program

Enter the option: c  ---- > create id1

Enter the name to add in the library: abcdasa

Entered value abcdasa


Generated id for the key abcdasa
 : 326548736

Enter the option: c ------> create id2

Enter the name to add in the library: hdafc

Entered value hdafc


Generated id for the key hdafc
 : 3120034304

Enter the option: d  ----> delete id1

Enter the ID to be deleted in the library: 326548736

Deleted the id : 326548736

Enter the option: c  ------> create id1

Enter the name to add in the library: abcdasa

Entered value abcdasa


Generated id for the key abcdasa
 : 326548737 ---------------> Duplicate ID for same entry with next sequentially incremented value 

Enter the option: s  -------> show current DB in the AVL tree including logically deleted ones as its not physically deleted yet

Printing all the IDs in the library

326548737 326548736 3120034304 

Enter the option: r ---------> Release the logically deleted entries in the DB (is_active - 0)

Releasing the inactive nodes in the library - started

Releasing the inactive nodes in the library - completed

Enter the option: s  --------> After cleanup activity, show operation of current DB shows that logically deleted ID was deleted permantently

Printing all the IDs in the library

326548737 3120034304 

Enter the option: e --------> exit from the application
Exiting from the application
~/IDManagement-Library$ 

Clarification:
------------

The final compiled binary files - idMgmt and unittest_idMgmt (application and unittest code) are uploaded as .txt file in github and cant able to modify it, please execute the makefile again using make command to get the proper binary file during verification.
  



