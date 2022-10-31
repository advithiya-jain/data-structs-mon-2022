#include<stdio.h>
#include<stdlib.h>
#include<time.h>

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

// ! Helper function for selection sort to swap values from two given int addresses
void swap (int* a, int* b){
    int t;
    t = *a;
    *a = *b;
    *b = t;
}

/**
 * ! Functon to selection sort a given array
 * This function takes in an array and the size of the array and sorts it using selection sort in ascending order
 * @param a is the array to be sorted
 * @param n is the size of the array
*/
void selectionSort(int* a, int n) {
    int min_index; // variable to store the index of the minimum value
    for (int i = 0; i < n-1; i++) { // loop to iterate through the array
        min_index = i; // setting the minimum index to the current index
        for (int j = i+1; j < n; j++) { // loop to iterate through the array from the next index
            if(a[j] < a[min_index]) { // if the value at the current index is lesser than the value at the minimum index
                min_index = j; // we set the minimum index to the current index
            }
        }
        swap(&a[min_index], &a[i]); // we swap the value at the minimum index with the value at the current index
    }
}

int main(int argc, char** argv) {
    int *a;
    int n, flag = 0;

    do {
        printf("Enter size of array: ");
        scanf("%d", &n);

        if(n < 1) {
            printf("\n Invalid input! >:C\n");
            flag = 1;
        }
    }while(flag == 1);

    // Generating the array of size n with random values
    a = generateArray(n);
    printf("\nYour randomly generated array is: ");
    printArray(a, n); // Printing the array
    // Selection sorting the array
    selectionSort(a, n);
    // Printing the sorted array
    printf("\nYour selection sorted array is: ");
    printArray(a, n);
    // Freeing the memory allocated to the array
    free(a);
    return 0;
}