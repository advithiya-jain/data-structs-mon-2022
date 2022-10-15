#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct node {
    int val;
    struct node* next;
};

typedef struct node node;

typedef struct {
    node* head;
    node* tail;
} queue;

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

int main(int argc, char** argv) {
    int n, flag = 0;

    srand(time(NULL));

    do {
        printf("Enter size of array: ");
        scanf("%d", &n);
        
        if(n < 1) {flag = 1; printf("Invalid Input >:C\n");}

    }while(flag == 1);

    return 0;
}