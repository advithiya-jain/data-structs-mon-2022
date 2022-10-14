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
 * //TODO: 1. create a generate array (rand vals) function. 
 * //TODO: 2. Function to generate a linked list from an array.
 * //TODO: 3. Supporting swap and max index functions for selection sort
 * //TODO: 4. Selection sort function for arrays. 
 * //TODO: 5. Print array and print linked list functions. 
 * //TODO: 6. main function to call functions (and srand() init)
*/

// ! Function to generate an array of given size 'n'
int* generateArray(int n) {
    // Creating a temporary array to use 
    int* temp = malloc(n * sizeof(int));
    if(temp) {
        for (int i = 0; i < n; i++)
        {
            temp[i] = rand()%1000; // using rand()%1000 to limit the number of digits in each element to 3.
        }
    }
    return temp; // returning the generated temp array.
}

// ! Function to generate a linked list from an array
NodeAddr arrToLinkedList(int* a, int n) {
    // initialising head and temp as node * type to be used to create a linked list.
    NodeAddr head, temp = NULL;

    //This is special case for the head. In this case n will always be > 0 since we are checking in main()
    if (n > 0) {
        head = malloc(sizeof(Node));
        head->value = a[0];
        head->next = NULL;
        temp = head;
    }
    // Now to the for loop that generates the rest of the list
    for(int i = 1; i < n; i++) {
        temp->next = malloc(sizeof(Node)); // First allocating space for the next node
        temp = temp->next; // now setting the current node to the next one (current temp on first iteration is head)
        temp->value = a[i]; // storing the value of a[i] into the value of temp
        temp->next = NULL; // making temp point to null (on last iteration temp points to NULL indicating end of list)
    }
    return head; // returning head we since we made temp = head so it will still point the next nodes.
}

/**
 * ! Function to print an array
 * @param a here is a an integer array (or int pointer to the first index of array 'a')
*/ 
void printArray(int* a, int n) {

    for (int i = 0; i < n; i++)
    {
        printf(i?", %d":"%d", a[i]);
    }
    printf(". :D\n");
    
}

/**
 * ! Function to print a linked list
 * @param head here is a pointer to the first node of a linked list (node type struct)
 * ? could use a NodeAddr* and pass printLinkedList(&head) instead as well but this would use a temp variable
 * ? may change other programs to do this as I guess that reduces space usage.
*/
void printLinkedList(NodeAddr head) {
    NodeAddr temp;

    for (temp = head; temp; temp = temp->next)
    {
        printf(temp==head?"%d":"->%d", temp->value);
    }
    printf(". :D\n");
    
}

// ! Helper function for selection sort to swap values from two given int addresses
void swap (int* a, int* b){
    int t;
    t = *a;
    *a = *b;
    *b = t;
}

// ! Helper function for selection for the "inner loop" of finding the largest value
int indexOfMax(int* a, int n){
    int max, i;

    //an error case if the array is empty (wont be in this program since we are checking in main)
    if (n < 1)
        return -1;
    
    max = 0; // Assuming a[0] has the largest element

    for(i = 1; i < n; i++) {
        if(a[i] > a[max])
            max = i; // here we are storing the index at which the largest element is present.
    }

    return max; // Returning the max index
}

// ! Function to selection sort a given array
void selectionSort(int* a, int n){
    int i, imax;

    for(i = n; i > 1; i--) {
        imax = indexOfMax(a, i);
        swap(&a[imax], &a[i-1]);
    }

}

// ! main function to call all other functions, take input and print results.
int main(int argc, char** argv) {
    // Initialising variables to be used
    int* a; 
    int n, flag = 0;
    NodeAddr list;

    srand(time(NULL)); // Initialising srand to use the current time in seconds as the seed.

    do { // Using a do while loop to keep asking for input in case of an invalid input
        printf("Enter size of the array: ");
        scanf("%d", &n);
        if(n < 1){ printf("Invalid input >:(\n"); flag = 1; }
    }while(flag == 1);

    a = generateArray(n);
    printf("\nYour randomly generated array is: ");
    printArray(a, n);

    list = arrToLinkedList(a, n);
    printf("\nYour array converted to a linked list is: ");
    printLinkedList(list);

    selectionSort(a, n);
    printf("\nYour sorted array is: ");
    printArray(a, n);

    list = arrToLinkedList(a, n);
    printf("\nYour sorted linked list is; ");
    printLinkedList(list);

    return 0;
}