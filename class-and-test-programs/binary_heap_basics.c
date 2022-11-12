#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

/**
 * ! Function to print an array
 * @param a here is a an integer array (or int pointer to the first index of array 'a')
 * @param n is the size of the array
*/ 
void printArray(int* a, int n) {

    if (n == 0) {
        printf("Empty array. :C\n");
        return;
    }
    else {
        for (int i = 0; i < n; i++)
        {
            printf(i?", %d":"%d", a[i]);
        }
        printf(". :D\n");
    }
}

/**
 * ! Helper function to swap two values
*/
void swap(int *x, int *y) {
    int t = *x;
    *x = *y;
    *y = t;
}

/**
 * TODO: Implement heap sort
*/

/**
 * ! Function to heapify the tree from the top to bottom of the tree
 * @param heap is the binary heap organised array 
 * @param n is the size of the heap
 * @param p is the index of the root of the tree
*/
void heapifyDown(int* heap, int n, int p) {
    int l = 2*p + 1; // left child of the parent p
    int r = 2*p + 2; // right child of the parent p
    int min = p; // min is the index of the smallest value (which should be the parent in the beginning)

    // if the left child is smaller than the min value (and is in the heap)
    if (l < n && heap[min] > heap[l]) { min = l; } // set the min value to the left child

    // Note: heap[min] is used instead of heap[p] because the min value may have changed
    // after the above if statement. This done to find the smallest of the 2 children.

    // if the right child is smaller than the min value (and is in the heap)
    if (r < n && heap[min] > heap[r]) { min = r; } // set the min value to the right child

    // if the min value is not the parent
    if (min != p) {
        // swap the parent with the min value
        swap(&heap[p], &heap[min]);
        // Recursively heapify the tree from the min value, 
        // the min value is now the parent for the reursive call.
        heapifyDown(heap, n, min);
    }
}

/**
 * ! Function to heapify up a tree from the bottom to the top of the tree.
 * @param heap is the heap to be fixed
 * @param n is the size of the heap
 * @param c is the last child of the heap
*/
void heapifyUp(int* heap, int n, int c) {
    int p = (c-1)/2; // parent of the child
    if (c <= 0) return; // if the child is the root or below index 0, return

    // if the parent is greater than the child,
    if (heap[p] > heap[c]) {
        // swap the parent and the child
        swap(&heap[p], &heap[c]);
        // Recursively call heapifyUp on the parent to fix the heap. 
        // The parent becomes the 'child' node for the recursive call.
        heapifyUp(heap, n, p);
    }
}

/**
 * ! Function to insert a value into a binary heap organised array
 * @param heap is the array to insert into
 * @param n is the size of the array
 * @param val is the value to be inserted
*/ 
int heapInsert(int* heap, int n, int val) {
    n++; // Incrementing the size of the array by 1
    int i = n-1; // Setting i to the last index
    heap[i] = val; // Inserting the value at the last index of the array

    heapifyUp(heap, n, i); // Calling heapifyUp to fix the heap

    return n; // Returning the new size of the array
}

/**
 * ! Function to delete the min value (root node) of a binary heap organised array
 * @param heap is the array to delete from
 * @param n is the address of the size of the array
 * * Using a pointer to n, as the value of n changes after the deletion of the min value.
*/
int heapExtract_min(int* heap, int* n) {
    if ((*n) == 0) return INT32_MAX; // If the heap is empty, return INT32_MAX
    int min = heap[0]; // Storing the min value in a variable
    heap[0] = heap[(*n)-1]; // Replacing the root node with the last node
    (*n)--; // Decrementing the size of the array by 1
    heapifyDown(heap, (*n), 0); // Calling heapifyDown to fix the heap
    return min; // Returning the min value
}

/**
 * ! Function to generate a min heap array with random values
 * @param heap is the array to be generated
 * @param n is the size of the array
*/
void generateHeap(int* heap, int n) {
    for (int i = 0; i < n; i++) {
        // Generating a random number between 0 and 99 and inserting it into the heap
        heapInsert(heap, i, rand()%100);
    }
}

/**
 * ! Function to generate a heap of size n based on user input n
 * @param n is address to the earlier value of n.
 * * A pointer to n is passed so that the value of n can be changed in the function.
 * * This is done as there is a re-generation of the heap option in the main function.
*/
int* userHeapGeneration(int *n) {
    int flag = 0;
    // Using a do while loop to keep asking for input if an invalid size in entered
    do {
        printf("Enter the size of the heap: ");
        scanf("%d", &(*n));
        if ((*n) <= 0) {
            printf("Invalid size! >:C\n");
            flag = 1;
        }
        else flag = 0;
    } while (flag == 1);
    
    // Initializing the heap array with the size n
    int* heap = malloc((*n) * sizeof(int));

    generateHeap(heap, (*n)); // Generating the heap with random values of size n.

    // Printing the generated heap
    printf("\nYour heap is: ");
    printArray(heap, (*n));

    return heap; // Returning the heap
}

int main(int argc, char** argv) {
    // opt is the option selected by the user in the menu below.
    // n is the size of the array, 
    // val is used to store the value to be inserted into the heap
    // t is a temp variable used for emptying the heap.
    int opt, n, val, t;
    int* heap = NULL; // Initializing the heap array to NULL

    srand(time(NULL)); // Initialising srand to use the current time in seconds as the seed
    
    printf("Welcome to this minimum binary heap editing program.\nUsing the Menu of options, you can perform min binary heap functions on a created min heap.\n");

    heap = userHeapGeneration(&n); // Generating the heap with random values of size n.

    while(true) {
        printf("\nMenu\n1: Re-Generate heap\n2: Extract min value\n3: Insert Value\n4: Display heap\n5: Empty heap\n6: Exit\n(enter one of these numbers to perform the corresponding action): ");
        scanf("%d", &opt);
        // Switch case to perform the corresponding menu action
        switch(opt) {
            case 1: // Re-Generating the heap array with random values
                    heap = userHeapGeneration(&n);
                    break;
            case 2: // Extracting the min value from the heap
                    printf("\nThe min value of: %d has been extracted\n", heapExtract_min(heap, &n));
                    break;
            case 3: // Inserting a value into the heap
                    printf("Enter the value to be inserted: ");
                    scanf("%d", &val);
                    
                    // We do n = heapInsert(...) because the size of the heap changes after insertion
                    n = heapInsert(heap, n, val); 
                    break;
            case 4: // Printing the heap array
                    if (n == 0) printf("\nThe heap is already empty!\n");
                    else {
                        printf("\nYour heap is: ");
                        printArray(heap, n);
                    }
                    break;
            case 5: // If the size of the heap is 0, the heap is already empty
                    if (n == 0) {
                        printf("\nThe heap is already empty!\n");
                        break;
                    }
                    // Else empty the heap
                    else {
                        // Loop that runs till n = 0.
                        // Extract the min value from the heap, since this changes the size of the heap,
                        // n will eventually become 0 and the function will then return an INT32_MAX.
                        while ((t = heapExtract_min(heap, &n))!= INT32_MAX);
                        printf("\nThe heap has been emptied! :D\n");
                    }
                    break;
            case 6: // Exiting the program
                    printf("\nExiting the program...\n");
                    free(heap); // Freeing the heap array
                    exit(0); // Exiting the program with exit code 0
                    break;
            default: // If an invalid option is entered
                    printf("\nInvalid option! >:C\n");
                    break;
        }
    }

    return 0;
}