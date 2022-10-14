#include<stdio.h>
#include<stdlib.h>
#include<time.h>

// Making node struct for linked lists 
struct nodeType {
    int value;
    struct nodeType* next;
};

// ! making NodeAddr a nodeType* struct for easier typing. basically a shortcut.
typedef struct nodeType* NodeAddr;
typedef struct nodeType Node; // same thing here but it is only nodeType (not a pointer)

/**
* TODO: 1. create a generate array (rand vals) function. 2. Function to convert array to linked list.
* TODO: 3. Selection sort function for arrays. 4. Supporting swap function for selectio sort
* TODO: 5. Print array and print linked list functions. 6. main function to call functions (and srand() init)
*/