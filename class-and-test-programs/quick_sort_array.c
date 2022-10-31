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

// ! Helper function for quick sort to swap values from two given int addresses
void swap (int* a, int* b){
    int t;
    t = *a;
    *a = *b;
    *b = t;
}

/**
 * ! Helper function to quick sort an array for the partitions
 * @param lower takes in the lower index to start with
 * @param higher takes in the higher index to end with
 * * This function basically returns a 'wall' which partitions the entered array
 * */ 
int quickPartition(int* a, int lower, int higher) {
    int pivot = a[higher]; // Setting the pivot to the higher index
    int ind_of_small = lower-1; // setting the index of the smaller index to the one before the lower index

    for(int i = lower; i < higher; i++) { // loop runs from lower to higher
        if(a[i] < pivot) { // If the element at index i is lesser than that of the pivot,
            ind_of_small++;// We increment ind_of_small, so as to make it point to the next value (as it is being swapped)
            swap(&a[ind_of_small], &a[i]); // And swap the index of the smaller value with that of i.
        }
    }
    // After exiting the loop, we swap the value at the index after the one at the smallest value and
    // the higher index value
    swap(&a[ind_of_small+1], &a[higher]);
    // Returning the next pivot index, which will be the one after the smaller value index
    return (ind_of_small+1);
}

/**
 * ! Recursive function to quick sort an array
 * @param low takes the beginning index of the array (when being called for the first time)
 * @param high takes the last index of the array (when being called for the first time)
 * * Since this is a recursive function, @param low and @param high can also be inferred as the lower index
 * * to start with and the higher index to end with (respectively)
 * ! It's void since it takes in a pointer(values will be modified while the pointer remains the same)
*/
void quickSort(int* a, int low, int high) {
    // Only recurses if the low index is before the high question
    if (low < high) {
        int p = quickPartition(a, low, high); // Partitioning the array and storing the wall in p

        // This sorts the 'left' half of the array, since we're starting from the low index till the wall
        quickSort(a, low, p - 1); 
        // This sorts the 'right' half, since we're starting after the wall till the high index.
        quickSort(a, p + 1, high);
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

    a = generateArray(n);
    printf("\nYour randomly generated array is: ");
    printArray(a, n);

    quickSort(a, 0, n-1);
    printf("\nYour quick sorted array is: ");
    printArray(a, n);

    return 0;
}