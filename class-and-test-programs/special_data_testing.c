#include<stdio.h>
#include<stdlib.h>

int arr_testing() {
    int *a;
    int i, n, val;
    n = 3;
    a = (int *) malloc(n * sizeof(int));

    // Enter Data
    scanf("%d", &val);
    i = 0;
    while(val > 0) {
        // do stuff
        a[i] = val;
        i++;
        if(i >= n) {
            // doubling size of array
            n = n*2;
            // reallocating a to double the size of earlier (size is stored in 'n')
            a = (int *) realloc(a, n * sizeof(int)); 
        }
        scanf("%d", &val);
    }
    // this to make sure the number of locations do not exceed the entered +ve numbers. This is to prevent
    // extra garbage-data being printed and allocated to a. 
    n = i;
    a = realloc(a, n * sizeof(int));

    // Printing values of a
    for(i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }

    printf("\n\nDone!\n");

    return 0;
}

struct nodeType {
    int value;
    struct nodeType* next;
};

// making Node a nodeType struct for easier typing. basically a shortcut.
typedef struct nodeType Node;

int main(int argc, char **argv) {
    int i, val;
    // holds the first address of struct nodeType (pointer)
    Node * head = NULL;
    // temp nodeType pointer.
    Node * temp = NULL;

    i = 0;
    
    scanf("%d", &val);
    while(val > 0) {
        temp = malloc(sizeof(Node));
        // *(temp) gives us the actual node itself. then the value inside is accessed and val is stored into it
        // ` *(temp).value = val; `
        temp->value = val; // does the same thing as the comented code above.
        temp->next = NULL;

        //if this is the first time

        //or else
        
        i++;
        scanf("%d", &val);
    }
    return 0;
}