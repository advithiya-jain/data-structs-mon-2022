#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

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
 * ! Helper function to swap two values
*/
void swap(int *x, int *y) {
    int t = *x;
    *x = *y;
    *y = t;
}

/**
 * ! Function to insert a value into a binary heap organised array
 * @param heap is the array to insert into
 * @param n is the size of the array
 * @param val is the value to be inserted
*/ 
void heapInsert(int* heap, int n, int val) {
    n++; // Incrementing the size of the array by 1
    int i = n-1; // Setting i to the last index
    heap[i] = val; // Inserting the value at the last index of the array

    // Loop that runs while the value at the parent node is greather than the current node
    while (i != 0 && heap[(i-1)/2] > heap[i]) {
        // Swap the values of the parent and current node (because the parent node always needs to be 
        // smaller or equal to the current/child nodes)
        swap(&heap[i], &heap[(i-1)/2]); 
        // And then set i to the parent node to keep checking for any min heap violations.
        i = (i-1)/2; 
    }
}

/**
 * ! Function to delete the min value (root node) of a binary heap organised array
 * @param heap is the array to delete from
 * @param n is the size of the array
*/
//int heapExtract_min(int* heap, int n) {
    
//};

int main(int argc, char** argv) {
    int n = 10;
    int* heap = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        heapInsert(heap, i, rand()%100);
    }

    printArray(heap, n);


    return 0;
}