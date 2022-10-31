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

/**
 * ! Function to insertion sort a given array
 * This function takes in an array and the size of the array and sorts it using insertion sort in ascending order
 * @param a is the array to be sorted
 * @param n is the size of the array
*/
void insertionSort(int* a, int n) {
    int key; // variable to store the 'key' value, this is the value that is going to be used for comparison
    int j; // variable to store the index of the previous element
    for (int i = 1; i < n; i++) { // loop to iterate through the array
        key = a[i]; // setting the key value to the current value
        j = i-1; // setting the index of the previous element to the current index - 1
        // while the index of the previous element is greater than or equal to 0 and the value at the index of the previous element is greater than the key value
        while (j >= 0 && a[j] > key) {
            a[j+1] = a[j]; // we set the value at the index of the previous element + 1 to the value at the index of the previous element
            j--; // we decrement the index of the previous element
        }
        a[j+1] = key; // After the loop we set the value at the index of the previous element + 1 to the key value
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
    // Insertion sorting the array
    insertionSort(a, n);
    // Printing the sorted array
    printf("\nYour insertion sorted array is: ");
    printArray(a, n);
    // Freeing the memory allocated to the array
    free(a);
    return 0;
}